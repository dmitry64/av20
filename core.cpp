#include "core.h"
#include <QDebug>
#include "device/modificators/gatemodificator.h"
#include "device/modificators/addgatemodificator.h"
#include "device/modificators/removegatemodificator.h"
#include "device/modificators/prismtimemodificator.h"

ChannelsCalibration * Core::getCalibrationsSnapshot()
{
    _calibrationSnapshotRequested.store(true);
    while(_calibrationSnapshotRequested.load()) {
        usleep(1);
    }
    return _calibrationsSnapshot;
}

TactTable *Core::getTactTable()
{
    return _currentMode->tactTables().at(_currentScheme);
}

TactTable *Core::getTactTableSnapshot()
{
    _tactTableSnapshotRequested.store(true);
    while(_tactTableSnapshotRequested.load()) {
        usleep(1);
    }
    return _tactTableSnapshot;
}

Device *Core::getDevice() const
{
    return _device;
}

ModeManager *Core::getModeManager() const
{
    return _modeManager;
}

Core::Core(ModeManager *modeManager, CalibrationManager * calibrationManager) : _active(true), _changesMutex(new QMutex())
{
    _modeManager = modeManager;
    _currentMode = 0;
    _device = new Device();
    _currentScheme = 0;
    _calibrationManager = calibrationManager;

    //_currentCalibration = new ChannelsCalibration();
    //_currentCalibration->init();
    _currentTactCounter = 0;

    _currentTact = 0;
    _line1CurrentAscan = new AScan();
    _line2CurrentAscan = new AScan();
    _calibrationSnapshotRequested.store(false);
    _calibrationsSnapshot = 0;
    _tactTableSnapshotRequested.store(false);
    _tactTableSnapshot = 0;
    _modeswitchRequested.store(false);
    _deviceOverheat = false;
    _deviceError = false;
    _deviceConnectionError = false;
}

Core::~Core()
{
    _active.store(false);
    this->wait();
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
    return _currentCalibration;
}

void Core::init()
{
    _device->init();
    _currentMode = _modeManager->modes().at(0);
    _currentScheme = 0;
    _currentCalibration = _calibrationManager->getLastCalibrationByTactID(_currentMode->tactTables().at(_currentScheme)->getId());
    TactTable * current = getTactTable();
    Q_ASSERT(current);
    _currentTact = current->getTactIndexByCounter(_currentTactCounter);
    _device->applyCalibration(_currentCalibration, current);
}

void Core::check()
{
    _device->checkConnection();
    handleDeviceConnectionError(_device->getErrorFlag());
}

void Core::trigger()
{
    TactTable * table = getTactTable();
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

void Core::aScanAll()
{
    std::vector< std::pair<uint8_t, uint8_t> > lines = getTactTable()->getTactLines(_currentTact);
    if(!lines.empty()) {
        for(size_t i=0; i<lines.size(); i++) {
            _device->getAscanForLine(lines[i].first,_line1CurrentAscan);
        }
    }
}

void Core::process()
{
    DisplayPackage * dp = new DisplayPackage();

    dp->ascan._samples.resize(ASCAN_SAMPLES_SIZE);

    dp->ascan._channel = _line1CurrentAscan->_header._channelNo;
    dp->bscan._channel = _line1CurrentAscan->_header._channelNo;

    uint16_t max = 0;
    uint16_t pos = 0;
    for(uint16_t i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        uint16_t sample = _line1CurrentAscan->_samples[i];
        if(sample >= max) {
            max = sample;
            pos = i;
        }
        dp->ascan._samples[i] = sample;
    }
    dp->ascan._markerPos = pos;
    dp->ascan._markerValue = max;

    std::vector<Gate> gates = _currentCalibration->getChannel(dp->bscan._channel)->rx()->gates();

    for(size_t j=0; j<gates.size(); j++) {
        Gate gate = gates[j];
        int gateStart = static_cast<int>(gate._start) * 4;
        int gateEnd = static_cast<int>(gate._finish) * 4;
        int start = -1;
        //int end = -1;
        bool startFound = false;
        for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
            uint8_t sample = _line1CurrentAscan->_samples[i];
            if((sample>gate._level) &&(!startFound) && (i >= gateStart) && (i <= gateEnd)) {
                start = i;
                startFound = true;
            } else if (startFound && (sample<gate._level || (i >= gateEnd))) {
                BScanDrawSample drawSample;
                drawSample._begin = start / 4;
                drawSample._end = i / 4;
                drawSample._level = gate._level;
                dp->bscan._samples.push_back(drawSample);
                startFound = false;
                start = -1;
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
        _calibrationsSnapshot = _currentCalibration->getSnapshot();
        _calibrationSnapshotRequested.store(false);
    }
    if(_tactTableSnapshotRequested.load()){
        _tactTableSnapshot = getTactTable()->getSnapshot();
        _tactTableSnapshotRequested.store(false);
    }
}

void Core::modeswitch()
{
    if(_modeswitchRequested.load()) {
        //_tactTable = _modeManager->modes().at(_requestedMode)->tactTables().at(_requestedScheme);
        _currentScheme = _requestedScheme;
        _currentMode =  _modeManager->modes().at(_requestedMode);
        _currentTact = 0;
        _currentTactCounter = 0;
        _currentCalibration = _calibrationManager->getLastCalibrationByTactID(_currentMode->tactTables().at(_currentScheme)->getId());
        _device->resetDevice();
        applyCurrentCalibrationToDevice();
        _modeswitchRequested.store(false);
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
    aScanAll();
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
    //qDebug() << "Overheat = " <<status;
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

void Core::notifyChannel(Channel channel)
{
    emit channelChanged(channel);
}

void Core::applyCurrentCalibrationToDevice()
{
    _device->applyCalibration(_currentCalibration, getTactTable());
}

void Core::addGate(uint8_t channel, Gate gate)
{
    qDebug() << "Add gate to channel" <<channel;
    AddGateModificator * mod = new AddGateModificator(channel,gate);
    addModificator(mod);
}

void Core::modifyGate(uint8_t channel, Gate gate)
{
    qDebug() << "Modify gate" << gate._id << "from channel" <<channel;
    GateModificator * mod = new GateModificator(channel,gate);
    addModificator(mod);
}

void Core::removeGate(uint8_t channel, uint8_t id)
{
    qDebug() << "Remove gate" << id << "from channel" <<channel;
    RemoveGateModificator * mod = new RemoveGateModificator(channel,id);
    addModificator(mod);
}

void Core::setPrismTime(uint8_t channel, uint8_t value)
{
    qDebug() << "Changing prism time ch =" << channel << "value =" <<value;
    PrismTimeModificator * mod = new PrismTimeModificator(channel,value);
    addModificator(mod);
}

void Core::setDeviceMode(uint8_t modeIndex, uint8_t schemeIndex)
{
    _requestedMode = modeIndex;
    _requestedScheme = schemeIndex;
    _modeswitchRequested.store(true);
    while(_modeswitchRequested.load()) {
        usleep(10);
    }
}

