#include "core.h"
#include <QDebug>
#include "device/modificators/gatemodificator.h"
#include "device/modificators/addgatemodificator.h"
#include "device/modificators/removegatemodificator.h"
#include "device/modificators/prismtimemodificator.h"
#include "device/modificators/pulserfreqmodificator.h"
#include "device/modificators/pulserprogmodificator.h"
#include "device/modificators/tvgmodificator.h"
#include "device/modificators/createcalibrationmodificator.h"
#include "device/modificators/removecalibrationmodificator.h"

ChannelsCalibration Core::getCalibrationsSnapshot()
{
    _calibrationSnapshotRequested.store(true);
    while(_calibrationSnapshotRequested.load()) {
        QThread::yieldCurrentThread();
    }
    return _calibrationsSnapshot;
}

CalibrationsInfoList Core::getAvailableCalibrationsSnapshot()
{
    _calibrationsInfoSnapshotRequested.store(true);
    while(_calibrationsInfoSnapshotRequested.load()) {
        QThread::yieldCurrentThread();
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
        QThread::yieldCurrentThread();
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

CalibrationManager *Core::getCalibrationManager() const
{
    return _calibrationManager;
}

Core::Core(ModeManager *modeManager, CalibrationManager * calibrationManager) : QObject(0),
    _active(true),
    _requestedMode(0),
    _requestedScheme(0),
    _requestedCalibration(0),
    _currentTactCounter(0),
    _currentTact(0),
    _device(new Device()),
    _modeManager(modeManager),
    _calibrationManager(calibrationManager),
    _deviceVersion(0),
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
    _registrationRequested.store(false);
    _registrationState = false;
    _finished.store(false);

    _registrationFileHandle = 0;
    _requestedChannelSelection._channel = 0;
    _requestedChannelSelection._displayChannel = 0;
}

Core::~Core()
{
    stopCore();
    delete _device;
    _changesMutex->unlock();
    delete _changesMutex;
    delete _line1CurrentAscan;
    delete _line2CurrentAscan;
}

void Core::work()
{
    init();
    //QElapsedTimer timer;
    while(_active) {
        //timer.start();
        searchWork();
        //qDebug() << timer.nsecsElapsed()/1000 << "ms";
        //QThread::msleep(20);
    }
    finish();
}

void Core::stopCore()
{
    logEvent("Core","Stopping core...");
    _active.store(false);
    while(!(_finished.load())) {
    }
    _device->finish();
    emit finished();
    logEvent("Core","Core exited");
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
    logEvent("Core","Core initializing");
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
    for(auto it=lines.begin(); it!=lines.end(); it++) {
        aScanProcess(it.operator*());
    }
}

void Core::aScanAll(const std::vector<uint8_t> &lines)
{
    if(Q_LIKELY(!lines.empty())) {
        for(auto it=lines.begin(); it!=lines.end(); it++) {
            auto val = it.operator*();
            if(val == 0) {
                _device->getAscanForLine(val,_line1CurrentAscan);
            }
            else if(val == 1) {
                _device->getAscanForLine(val,_line2CurrentAscan);
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

    dp->_ascan._samples.resize(ASCAN_SAMPLES_SIZE);

    dp->_ascan._channel = chId;
    dp->_bscan._info._channel = chId;
    dp->_bscan._info._displayChannel = current.getActiveDisplayChannelIndex();

    uint16_t max = 0;
    uint16_t pos = 0;
    for(uint16_t i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        uint16_t sample = scanptr->_samples[i];
        if(sample >= max) {
            max = sample;
            pos = i;
        }
        dp->_ascan._samples[i] = sample;
    }
    dp->_ascan._markerPos = pos;
    dp->_ascan._markerValue = max;

    const DisplayChannel & dispChannel = current.getActiveDisplayChannel();
    const std::vector<Gate> & gates = dispChannel.gates();

    for(auto it=gates.begin(); it!=gates.end(); it++) {
        const Gate & gate = it.operator*();
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
                dp->_bscan._samples.push_back(drawSample);
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

    if(_registrationFileHandle!=0) {
        delete _registrationFileHandle;
        _registrationFileHandle = 0;
    }

    _calibrationManager->saveAll();
    _device->finish();
    _finished.store(true);
}

void Core::searchWork()
{
    snapshot();
    check();
    trigger();
    status();
    process();
    registration();
    sync();
    modeswitch();
}

void Core::registration()
{
    if(_registrationRequested.load()) {
        if(!_registrationState) {
            // start
            Q_ASSERT(_registrationOutputPath.length() > 0);
            _registrationFileHandle = new QFile(_registrationOutputPath);
            _registrationFileHandle->open(QIODevice::WriteOnly);
            _registrationState = true;
            emit registrationStateChanged(true);
        }
        else {
            // continue
            _registrationFileHandle->write(reinterpret_cast<char*>(_line1CurrentAscan),sizeof(AScan));
            _registrationFileHandle->write(reinterpret_cast<char*>(_line2CurrentAscan),sizeof(AScan));
        }
    }
    else {
        if(_registrationState) {
            //stop
            _registrationFileHandle->close();
            _registrationState = false;
            delete _registrationFileHandle;
            _registrationFileHandle = 0;
            emit registrationStateChanged(false);
        }
    }
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
            logEvent("Core","Device error!");
        }
        else {
            _deviceError = false;
            emit deviceErrorDisable();
            logEvent("Core","Device restored!");
        }
    }
}

void Core::handleDeviceOverheat(bool status)
{
    if(_deviceOverheat!=status) {
        if(_deviceOverheat == false) {
            _deviceOverheat = true;
            emit deviceOverheatEnable();
            logEvent("Core","Device overheat!");
        }
        else {
            _deviceOverheat = false;
            emit deviceOverheatDisable();
            logEvent("Core","Device cooled!");
        }
    }
}

void Core::handleDeviceConnectionError(bool status)
{
    if(_deviceConnectionError!=status) {
        if(_deviceConnectionError == false) {
            _deviceConnectionError = true;
            emit deviceConnectionErrorEnable();
            logEvent("Core","Connection error!");
        }
        else {
            _deviceConnectionError = false;
            emit deviceConnectionErrorDisable();
            logEvent("Core","Connection restored!");
        }
    }
}

void Core::notifyChannel(const Channel &channel)
{
    emit channelChanged(channel);
}

void Core::notifyCalibration()
{
    emit calibrationChanged();
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

void Core::addGate(const ChannelsInfo & info, const Gate & gate)
{
    logEvent("Core","Add gate to channel #" + QString::number(info._channel) + " Gate id="+QString::number(gate._id));
    AddGateModificator * mod = new AddGateModificator(info,gate);
    addModificator(mod);
}

void Core::modifyGate(const ChannelsInfo & info,const Gate & gate)
{
    logEvent("Core","Modify gate on channel #" + QString::number(info._channel) + " Gate id="+QString::number(gate._id));
    GateModificator * mod = new GateModificator(info,gate);
    addModificator(mod);
}

void Core::removeGate(const ChannelsInfo & info,const uint8_t id)
{
    logEvent("Core","Remove gate on channel #" + QString::number(info._channel) + " Gate id="+QString::number(id));
    RemoveGateModificator * mod = new RemoveGateModificator(info,id);
    addModificator(mod);
}

void Core::setPrismTime(const ChannelsInfo & info,const uint8_t value)
{
    logEvent("Core","Set prism time to channel #" + QString::number(info._channel));
    PrismTimeModificator * mod = new PrismTimeModificator(info,value);
    addModificator(mod);
}

void Core::setPulserFreq(const ChannelsInfo &info, const PulserFreq value)
{
    logEvent("Core","Set pulser freq to channel #" + QString::number(info._channel));
    PulserFreqModificator * mod = new PulserFreqModificator(info,value);
    addModificator(mod);
}

void Core::setPulserProg(const ChannelsInfo &info, const PulserProg value)
{
    logEvent("Core","Set pulser prog to channel #" + QString::number(info._channel));
    PulserProgModificator * mod = new PulserProgModificator(info,value);
    addModificator(mod);
}

void Core::setTVG(const ChannelsInfo & info, const TVGCurve *ptr)
{
    logEvent("Core","Set TVG to channel #" + QString::number(info._channel));
    TVGCurve * curve = ptr->clone();
    Q_ASSERT(curve);
    TVGModificator * mod = new TVGModificator(info,curve);
    addModificator(mod);
}

void Core::setDeviceMode(const DeviceModeIndex modeIndex,const SchemeIndex schemeIndex)
{
    _requestedMode = modeIndex;
    _requestedScheme = schemeIndex;
    _modeswitchRequested.store(true);
    while(_modeswitchRequested.load()) {
        QThread::yieldCurrentThread();
    }
    emit modeChanged();
}

void Core::switchCalibration(const CalibrationIndex index)
{
    _requestedCalibration = index;
    _calibrationSwitchRequested.store(true);
    while(_calibrationSwitchRequested.load()) {
        QThread::yieldCurrentThread();
    }
    emit calibrationChanged();
}

void Core::switchChannel(const ChannelsInfo & info)
{
    _requestedChannelSelection = info;
    _channelSwitchRequested.store(true);
    while(_channelSwitchRequested.load()) {
        QThread::yieldCurrentThread();
    }
}

void Core::createCalibration(const CalibrationIndex baseIndex,const QString & name)
{
    logEvent("Core","Creating new calibration from #" + QString::number(baseIndex)+" name: "+name);
    CreateCalibrationModificator * mod = new CreateCalibrationModificator(baseIndex,name);
    addModificator(mod);
}

void Core::removeCalibration(const CalibrationIndex index)
{
    logEvent("Core","Removing calibration #" + QString::number(index));
    RemoveCalibrationModificator * mod = new RemoveCalibrationModificator(index);
    addModificator(mod);
}

void Core::startRegistration(const QString & outputFile)
{
    _registrationOutputPath = outputFile;
    _registrationRequested.store(true);
}

void Core::stopRegistration()
{
    _registrationRequested.store(false);
}

void Core::handleChannelSelection(const ChannelsInfo & info)
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
