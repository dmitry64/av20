#include "core.h"
#include <QDebug>
#include "device/modificators/gatemodificator.h"
#include "device/modificators/addgatemodificator.h"
#include "device/modificators/removegatemodificator.h"
#include "device/modificators/prismtimemodificator.h"
#include "device/modificators/tvgmodificator.h"

ChannelsCalibration Core::getCalibrationsSnapshot()
{
    _calibrationSnapshotRequested.store(true);
    while(_calibrationSnapshotRequested.load()) {
        usleep(1);
    }
    return _calibrationsSnapshot;
}

CalibrationsInfoList Core::getAvailableCalibrationsSnapshot()
{
    _calibrationsInfoSnapshotRequested.store(true);
    while(_calibrationsInfoSnapshotRequested.load()) {
        usleep(1);
    }
    return _calibrationsInfoListSnapshot;
}

TactTable Core::getTactTable()
{
    return getCurrentDeviceMode().tactTables().at(_currentScheme);
}

TactTable Core::getTactTableSnapshot()
{
    _tactTableSnapshotRequested.store(true);
    while(_tactTableSnapshotRequested.load()) {
        usleep(1);
    }
    return _tactTableSnapshot;
}

const ModeManager *Core::getModeManager() const
{
    return _modeManager;
}

SchemeIndex Core::getCurrentScheme() const
{
    return _currentScheme.load();
}

DeviceModeIndex Core::getCurrentMode() const
{
    return _currentMode.load();
}

CalibrationIndex Core::getCurrentCalibration() const
{
    return _currentCalibration.load();
}

Core::Core(ModeManager *modeManager, CalibrationManager * calibrationManager) :
    _active(true),
    _requestedMode(0),
    _requestedScheme(0),
    _requestedCalibration(0),
    _currentTactCounter(0),
    _currentTact(0),
    _device(new Device()),
    _modeManager(modeManager),
    _calibrationManager(calibrationManager),
    _deviceOverheat(false),
    _deviceError(false),
    _deviceConnectionError(false),
    _changesMutex(new QMutex())

{
    Q_ASSERT(modeManager);
    Q_ASSERT(calibrationManager);

    _currentScheme.store(0);
    _currentCalibration.store(0);
    _currentMode.store(0);
    _currentTactCounter = 0;
    _currentTact = 0;
    _line1CurrentAscan = new AScan();
    _line2CurrentAscan = new AScan();
    _calibrationSnapshotRequested.store(false);
    _tactTableSnapshotRequested.store(false);
    _modeswitchRequested.store(false);
    _calibrationsInfoSnapshotRequested.store(false);
    _calibrationSwitchRequested.store(false);
    _channelSwitchRequested.store(false);

    _requestedChannelSelection._channel = 0;
    _requestedChannelSelection._displayChannel = 0;
}

Core::~Core()
{
    _active.store(false);
    this->wait();
    delete _device;
    delete _line1CurrentAscan;
    delete _line2CurrentAscan;
}

void Core::run()
{
    init();
    while(_active) {
        searchWork();
    }
    finish();
}

void Core::stopCore()
{
    _active.store(false);
    this->wait();
}

ChannelsCalibration Core::getCalibration()
{
    const DeviceMode & currentMode = getCurrentDeviceMode();
    const auto & tables = currentMode.tactTables();
    TactID id = tables.at(_currentScheme).getId();
    const auto & cals = _calibrationManager->getCalibrationsByTactID(id);
    return cals.at(_currentCalibration.load());
}

DeviceMode Core::getCurrentDeviceMode()
{
    return _modeManager->modes().at(_currentMode.load());
}

void Core::init()
{
    _device->init(&_deviceVersion);
    _currentScheme.store(0);
    _currentCalibration.store(0);
    _currentMode.store(0);
    TactTable current = getTactTable();
    _currentTact = current.getTactIndexByCounter(_currentTactCounter);
    Q_ASSERT(_currentTact<8);
    _device->applyCalibration(getCalibration(), current);
    logEvent("Core","Core initialized!");
    emit displayVersion(getVersionString(_deviceVersion));
}

void Core::check()
{
    _device->checkConnection();
    handleDeviceConnectionError(_device->getErrorFlag());
}

void Core::trigger()
{
    const TactTable & table = getTactTable();
    if(Q_LIKELY(table.getMaxTacts() > 0)) {
        _device->setProgTrigger(true);
        _currentTactCounter++;
        if(_currentTactCounter>=table.getMaxTacts()) {
            _currentTactCounter = 0;
        }
        _currentTact = table.getTactIndexByCounter(_currentTactCounter);
    }
}

void Core::status()
{
    DeviceStatus status = _device->getDeviceStatus();

    handleDeviceError(status.error);
    handleDeviceOverheat(status.thsd);

    DeviceStatus current = status;
    while(!current.ready) {
        usleep(1);
        current = _device->getDeviceStatus();
        handleDeviceError(current.error);
        handleDeviceOverheat(current.thsd);
    }
    _device->setProgTrigger(false);
}

void Core::process()
{
    const std::vector< uint8_t > & lines = getTactTable().getTactLines(_currentTact);
    aScanAll(lines);
    uint8_t count = lines.size();
    for(uint8_t i=0; i<count; i++) {
        aScanProcess(lines[i]);
    }
}

void Core::aScanAll(const std::vector<uint8_t> &lines)
{
    if(Q_LIKELY(!lines.empty())) {
        for(size_t i=0; i<lines.size(); i++) {
            if(lines[i] == 0) {
                _device->getAscanForLine(lines[i],_line1CurrentAscan);
            }
            else if(lines[i] == 1) {
                _device->getAscanForLine(lines[i],_line2CurrentAscan);
            }
            else {
                Q_ASSERT(false);
            }
        }
    }
}

void Core::aScanProcess(uint8_t line)
{
    AScan * scanptr = 0;

    if(line == 0) {
        scanptr = _line1CurrentAscan;
    }
    else if (line == 1) {
        scanptr = _line2CurrentAscan;
    }
    else {
        Q_ASSERT(false);
    }

    ChannelID chId = scanptr->_header._channelNo;
    Q_ASSERT(chId < 8);

    const ChannelsCalibration & calibration = getCalibration();
    const Channel & current = calibration.getChannel(chId);

    DisplayPackage * dp = new DisplayPackage();

    dp->ascan._samples.resize(ASCAN_SAMPLES_SIZE);

    dp->ascan._channel = chId;
    dp->bscan._info._channel = chId;
    dp->bscan._info._displayChannel = current.getActiveDisplayChannelIndex();

    uint16_t max = 0;
    uint16_t pos = 0;
    for(uint16_t i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        uint16_t sample = scanptr->_samples[i];
        if(sample >= max) {
            max = sample;
            pos = i;
        }
        dp->ascan._samples[i] = sample;
    }
    dp->ascan._markerPos = pos;
    dp->ascan._markerValue = max;

    const DisplayChannel & dispChannel =current.getActiveDisplayChannel();
    const std::vector<Gate> & gates = dispChannel.gates();

    for(uint8_t j=0; j<gates.size(); j++) {
        const Gate & gate = gates[j];
        uint16_t gateStart = (gate._start) * 4;
        uint16_t gateEnd = (gate._finish) * 4;
        uint16_t start = 0;
        bool startFound = false;
        for(uint16_t i=0; i<ASCAN_SAMPLES_SIZE; i++) {
            uint8_t sample = scanptr->_samples[i];
            if((sample>gate._level) &&(!startFound) && (i >= gateStart) && (i <= gateEnd)) {
                start = i;
                startFound = true;
            }
            else if (startFound && (sample<gate._level || (i >= gateEnd))) {
                BScanDrawSample drawSample;
                drawSample._begin = start / 0x0004;
                drawSample._end = i / 0x0004;
                drawSample._level = gate._level;
                dp->bscan._samples.push_back(drawSample);
                startFound = false;
                start = 0;
            }
        }
    }

    emit drawDisplayPackage(QSharedPointer<DisplayPackage>(dp));
}

void Core::sync()
{
    // emit to ui
    if(_changesMutex->tryLock()) {
        while(Q_UNLIKELY(!_pendingChanges.empty())) {
            Modificator * mod = _pendingChanges.front();
            Q_ASSERT(mod);
            mod->apply(this);
            delete mod;
            _pendingChanges.pop();
        }
        _changesMutex->unlock();
    }
    // apply from ui
}

void Core::snapshot()
{
    if(_calibrationSnapshotRequested.load()) {
        _calibrationsSnapshot = getCalibration().getSnapshot();
        _calibrationSnapshotRequested.store(false);
    }
    if(_tactTableSnapshotRequested.load()) {
        _tactTableSnapshot = getTactTable().getSnapshot();
        _tactTableSnapshotRequested.store(false);
    }
    if(_calibrationsInfoSnapshotRequested.load()) {
        _calibrationsInfoListSnapshot = _calibrationManager->getCalibrationsInfoByTactID(getCurrentDeviceMode().tactTables().at(_currentScheme).getId());
        _calibrationsInfoSnapshotRequested.store(false);
    }
}

void Core::modeswitch()
{
    if(_modeswitchRequested.load()) {
        _currentScheme.store(_requestedScheme);
        _currentMode.store(_requestedMode);
        _currentTact = 0;
        _currentTactCounter = 0;
        _currentCalibration.store(0);
        _device->resetDevice();
        applyCurrentCalibrationToDevice();
        _modeswitchRequested.store(false);
    }
    if(_calibrationSwitchRequested.load()) {
        _currentCalibration.store(_requestedCalibration);
        applyCurrentCalibrationToDevice();
        _calibrationSwitchRequested.store(false);
    }
    if(_channelSwitchRequested.load()) {
        handleChannelSelection(_requestedChannelSelection);
        _channelSwitchRequested.store(false);
    }
}

void Core::finish()
{
    logEvent("Core","Disconnected!");
}

void Core::searchWork()
{
    snapshot();
    check();
    trigger();
    status();
    process();
    sync();
    modeswitch();
    //msleep(2);
}

void Core::addModificator(Modificator *mod)
{
    _changesMutex->lock();
    _pendingChanges.push(mod);
    _changesMutex->unlock();
}

void Core::handleDeviceError(bool status)
{
    if(_deviceError!=status) {
        if(_deviceError == false) {
            _deviceError = true;
            emit deviceErrorEnable();
        }
        else {
            _deviceError = false;
            emit deviceErrorDisable();
        }
    }
}

void Core::handleDeviceOverheat(bool status)
{
    if(_deviceOverheat!=status) {
        if(_deviceOverheat == false) {
            _deviceOverheat = true;
            emit deviceOverheatEnable();
        }
        else {
            _deviceOverheat = false;
            emit deviceOverheatDisable();
        }
    }
}

void Core::handleDeviceConnectionError(bool status)
{
    if(_deviceConnectionError!=status) {
        if(_deviceConnectionError == false) {
            _deviceConnectionError = true;
            emit deviceConnectionErrorEnable();
        }
        else {
            _deviceConnectionError = false;
            emit deviceConnectionErrorDisable();
        }
    }
}

void Core::notifyChannel(Channel channel)
{
    emit channelChanged(channel);
}

void Core::applyChannelsModification(ChannelID index, Channel channel)
{
    const auto & calib = getCalibration();
    _calibrationManager->applyChannelsModification(calib.getTactId(),_currentCalibration.load(), index, channel);
}

void Core::applyCurrentCalibrationToDevice()
{
    _device->applyCalibration(getCalibration(), getTactTable());
}

void Core::addGate(const ChannelsInfo info, const Gate & gate)
{
    logEvent("Core","Add gate to channel #" + QString::number(info._channel));
    AddGateModificator * mod = new AddGateModificator(info,gate);
    addModificator(mod);
}

void Core::modifyGate(const ChannelsInfo info,const Gate & gate)
{
    logEvent("Core","Modify gate to channel #" + QString::number(info._channel));
    GateModificator * mod = new GateModificator(info,gate);
    addModificator(mod);
}

void Core::removeGate(const ChannelsInfo info,const uint8_t id)
{
    logEvent("Core","Remove gate to channel #" + QString::number(info._channel));
    RemoveGateModificator * mod = new RemoveGateModificator(info,id);
    addModificator(mod);
}

void Core::setPrismTime(const ChannelsInfo info,const uint8_t value)
{
    logEvent("Core","Set prism time to channel #" + QString::number(info._channel));
    PrismTimeModificator * mod = new PrismTimeModificator(info,value);
    addModificator(mod);
}

void Core::setTVG(const ChannelsInfo info, const TVGCurve *ptr)
{
    logEvent("Core","Set TVG to channel #" + QString::number(info._channel));
    TVGCurve * curve = ptr->clone();
    TVGModificator * mod = new TVGModificator(info,curve);
    addModificator(mod);
}

void Core::setDeviceMode(const DeviceModeIndex modeIndex,const SchemeIndex schemeIndex)
{
    _requestedMode = modeIndex;
    _requestedScheme = schemeIndex;
    _modeswitchRequested.store(true);
    while(_modeswitchRequested.load()) {
        usleep(1);
    }
    emit modeChanged();
}

void Core::switchCalibration(const CalibrationIndex index)
{
    _requestedCalibration = index;
    _calibrationSwitchRequested.store(true);
    while(_calibrationSwitchRequested.load()) {
        usleep(1);
    }
    emit calibrationChanged();
}

void Core::switchChannel(const ChannelsInfo info)
{
    _requestedChannelSelection = info;
    _channelSwitchRequested.store(true);
    while(_channelSwitchRequested.load()) {
        usleep(1);
    }
}

void Core::handleChannelSelection(const ChannelsInfo info)
{
    logEvent("Core","Handling channel selection - new channel #" + QString::number(info._channel));
    const DeviceMode & currentMode = getCurrentDeviceMode();
    if(currentMode.type() == ModeTypes::SingleChannelMode) {
        const auto & calibration = getCalibration();
        auto channel = calibration.getChannel(info._channel);
        if(channel.getActiveDisplayChannelIndex()!=info._displayChannel) {
            channel.setActiveDisplayChannelIndex(info._displayChannel);
            applyChannelsModification(info._channel,channel);
            applyCurrentCalibrationToDevice();
            notifyChannel(channel);
        }
    }
}
