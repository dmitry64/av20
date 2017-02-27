#include "core.h"
#include <QDebug>
#include "device/modificators/gatemodificator.h"
#include "device/modificators/addgatemodificator.h"
#include "device/modificators/removegatemodificator.h"
#include "device/modificators/prismtimemodificator.h"
#include "device/modificators/tvgmodificator.h"

ChannelsCalibration * Core::getCalibrationsSnapshot()
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

TactTable *Core::getTactTable()
{
    return getCurrentDeviceMode()->tactTables().at(_currentScheme);
}

TactTable *Core::getTactTableSnapshot()
{
    _tactTableSnapshotRequested.store(true);
    while(_tactTableSnapshotRequested.load()) {
        usleep(1);
    }
    return _tactTableSnapshot;
}

ModeManager *Core::getModeManager() const
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

Core::Core(ModeManager *modeManager, CalibrationManager * calibrationManager) : _active(true), _changesMutex(new QMutex())
{
    Q_ASSERT(modeManager);
    Q_ASSERT(calibrationManager);
    _modeManager = modeManager;
    _device = new Device();
    _currentScheme.store(0);
    _currentCalibration.store(0);
    _currentMode.store(0);
    _calibrationManager = calibrationManager;
    _currentTactCounter = 0;
    _currentTact = 0;
    _line1CurrentAscan = new AScan();
    _line2CurrentAscan = new AScan();
    _calibrationSnapshotRequested.store(false);
    _calibrationsSnapshot = 0;
    _tactTableSnapshotRequested.store(false);
    _tactTableSnapshot = 0;
    _modeswitchRequested.store(false);
    _calibrationsInfoSnapshotRequested.store(false);
    _calibrationSwitchRequested.store(false);
    _deviceOverheat = false;
    _deviceError = false;
    _deviceConnectionError = false;
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

ChannelsCalibration *Core::getCalibration()
{
    return _calibrationManager->getCalibrationsByTactID(getCurrentDeviceMode()->tactTables().at(_currentScheme)->getId()).at(_currentCalibration.load());
}

DeviceMode *Core::getCurrentDeviceMode()
{
    return _modeManager->modes().at(_currentMode.load());
}

void Core::init()
{
    _device->init();
    _currentScheme.store(0);
    _currentCalibration.store(0);
    _currentMode.store(0);
    TactTable * current = getTactTable();
    Q_ASSERT(current);
    _currentTact = current->getTactIndexByCounter(_currentTactCounter);
    Q_ASSERT(_currentTact<8);
    _device->applyCalibration(getCalibration(), current);
}

void Core::check()
{
    _device->checkConnection();
    handleDeviceConnectionError(_device->getErrorFlag());
}

void Core::trigger()
{
    TactTable * table = getTactTable();
    Q_ASSERT(table);
    if(table->getMaxTacts() > 0) {
        _device->setProgTrigger(true);
        _currentTactCounter++;
        if(_currentTactCounter>=table->getMaxTacts()) {
            _currentTactCounter = 0;
        }
        _currentTact = table->getTactIndexByCounter(_currentTactCounter);
    }
}

void Core::status()
{
    DeviceStatus status = _device->getDeviceStatus();

    handleDeviceError(status.error);
    handleDeviceOverheat(status.thsd);

    DeviceStatus current = status;
    while(!current.ready) {
        usleep(10);
        current = _device->getDeviceStatus();
        handleDeviceError(current.error);
        handleDeviceOverheat(current.thsd);
    }
    _device->setProgTrigger(false);
}

void Core::process()
{
    std::vector< uint8_t > lines = getTactTable()->getTactLines(_currentTact);
    aScanAll(lines);
    for(size_t i=0; i<lines.size(); i++) {
        aScanProcess(lines[i]);
    }
}

void Core::aScanAll(std::vector< uint8_t > lines)
{
    if(!lines.empty()) {
        for(size_t i=0; i<lines.size(); i++) {
            if(lines[i] == 0) {
                _device->getAscanForLine(lines[i],_line1CurrentAscan);
            } else if(lines[i] == 1){
                _device->getAscanForLine(lines[i],_line2CurrentAscan);
            } else {
                Q_ASSERT(false);
            }
        }
    }
}

void Core::aScanProcess(uint8_t line)
{
    DisplayPackage * dp = new DisplayPackage();

    dp->ascan._samples.resize(ASCAN_SAMPLES_SIZE);
    AScan * scanptr = 0;

    if(line == 0) {
        scanptr = _line1CurrentAscan;
    } else if (line == 1) {
        scanptr = _line2CurrentAscan;
    } else {
        Q_ASSERT(false);
    }

    dp->ascan._channel = scanptr->_header._channelNo;
    dp->bscan._channel = scanptr->_header._channelNo;

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

    std::vector<Gate> gates = getCalibration()->getChannel(dp->bscan._channel)->rx()->gates();

    for(size_t j=0; j<gates.size(); j++) {
        Gate gate = gates[j];
        uint16_t gateStart = (gate._start) * 4;
        uint16_t gateEnd = (gate._finish) * 4;
        uint16_t start = 0;
        //int end = -1;
        bool startFound = false;
        for(uint16_t i=0; i<ASCAN_SAMPLES_SIZE; i++) {
            uint8_t sample = scanptr->_samples[i];
            if((sample>gate._level) &&(!startFound) && (i >= gateStart) && (i <= gateEnd)) {
                start = i;
                startFound = true;
            } else if (startFound && (sample<gate._level || (i >= gateEnd))) {
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
    if(_changesMutex->tryLock())
    {
        while(!_pendingChanges.empty()) {
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
        _calibrationsSnapshot = getCalibration()->getSnapshot();
        _calibrationSnapshotRequested.store(false);
    }
    if(_tactTableSnapshotRequested.load()) {
        _tactTableSnapshot = getTactTable()->getSnapshot();
        _tactTableSnapshotRequested.store(false);
    }
    if(_calibrationsInfoSnapshotRequested.load()) {
        _calibrationsInfoListSnapshot = _calibrationManager->getCalibrationsInfoByTactID(getCurrentDeviceMode()->tactTables().at(_currentScheme)->getId());
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
}

void Core::finish()
{
    qDebug() << "Disconnected!";
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
        } else {
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
        } else {
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
        } else {
            _deviceConnectionError = false;
            emit deviceConnectionErrorDisable();
        }
    }
}

void Core::notifyChannel(Channel *channel)
{
    Q_ASSERT(channel);
    emit channelChanged(channel);
}

void Core::applyCurrentCalibrationToDevice()
{
    _device->applyCalibration(getCalibration(), getTactTable());
}

void Core::addGate(ChannelID channel, Gate gate)
{
    //qDebug() << "Add gate to channel" <<channel;
    AddGateModificator * mod = new AddGateModificator(channel,gate);
    addModificator(mod);
}

void Core::modifyGate(ChannelID channel, Gate gate)
{
    //qDebug() << "Modify gate" << gate._id << "from channel" <<channel;
    GateModificator * mod = new GateModificator(channel,gate);
    addModificator(mod);
}

void Core::removeGate(ChannelID channel, uint8_t id)
{
    //qDebug() << "Remove gate" << id << "from channel" <<channel;
    RemoveGateModificator * mod = new RemoveGateModificator(channel,id);
    addModificator(mod);
}

void Core::setPrismTime(ChannelID channel, uint8_t value)
{
    //qDebug() << "Changing prism time ch =" << channel << "value =" <<value;
    PrismTimeModificator * mod = new PrismTimeModificator(channel,value);
    addModificator(mod);
}

void Core::setTVG(ChannelID channel, TVGCurve *ptr)
{
    //qDebug() << "Changing tvg for ch =" <<channel;
    TVGCurve * curve = ptr->clone();
    TVGModificator * mod = new TVGModificator(channel,curve);
    addModificator(mod);
}

void Core::setDeviceMode(DeviceModeIndex modeIndex, SchemeIndex schemeIndex)
{
    _requestedMode = modeIndex;
    _requestedScheme = schemeIndex;
    _modeswitchRequested.store(true);
    while(_modeswitchRequested.load()) {
        usleep(1);
    }
    emit modeChanged();
}

void Core::switchCalibration(CalibrationIndex index)
{
    _requestedCalibration = index;
    _calibrationSwitchRequested.store(true);
    while(_calibrationSwitchRequested.load()){
        usleep(1);
    }
    emit calibrationChanged();
}

