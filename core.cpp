#include "core.h"
#include <QDebug>
#include "device/modificators/tvgsimplemodificator.h"

DeviceCalibration * Core::getSnapshot()
{
    _snapshotRequested.store(true);
    while(_snapshotRequested.load()) {
        usleep(1);
    }
    return _snapshot;
}

Device *Core::getDevice() const
{
    return _device;
}

Core::Core() : _active(true), _state(new DeviceState()), _deviceMode(DEVICE_MODE_EVAL), _targetChannel(0), _changesMutex(new QMutex())
{
    _device = (new Device(_state));
    _currentCalibration = new DeviceCalibration();
    _currentCalibration->init();
    _currentTactCounter = 0;
    _currentTact = _currentCalibration->getTactIndexByCounter(_currentTactCounter);
    _snapshotRequested.store(false);
    _snapshot = 0;
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
        switch (_deviceMode.load()) {
        case DEVICE_MODE_EVAL:
            //evaluationWork();
            //break;
        case DEVICE_MODE_SEARCH:
            searchWork();
            break;
        case DEVICE_MODE_HEAD_SCANNER:
            break;
        case DEVICE_MODE_WHEEL:
            break;
        default:
            qFatal("Unknown mode!");
            break;
        }
    }
    finish();
}

DeviceCalibration *Core::getCalibration()
{
    return _currentCalibration;
}

void Core::init()
{
    _device->init();
    _device->applyCalibration(_currentCalibration);
}

void Core::check()
{
    emit connection(_device->checkConnection());
    emit connectionError(_device->getErrorFlag());
}

void Core::trigger()
{
    if(_currentCalibration->getMaxTacts() > 0) {

        _device->setProgTrigger(true);
        _currentTactCounter++;
        if(_currentTactCounter>=_currentCalibration->getMaxTacts()) {
            _currentTactCounter = 0;
        }

        _currentTact = _currentCalibration->getTactIndexByCounter(_currentTactCounter);
    }
}

void Core::status()
{
    DeviceStatus status = _device->getDeviceStatus();
    emit deviceError(status.error);
    emit deviceOverheat(status.thsd);
    emit deviceReady(status.ready);
    DeviceStatus current = status;
    while(!current.ready) {
        current = _device->getDeviceStatus();
        if(status.error!=current.error) {
            emit deviceError(current.error);
        }
        if(status.thsd!=current.thsd) {
            emit deviceOverheat(current.thsd);
        }
        if(status.ready!=current.ready) {
            emit deviceReady(current.ready);
        }
        usleep(100);
    }
    _device->setProgTrigger(false);
}

void Core::aScanAll()
{
    std::vector< std::pair<uint8_t, uint8_t> > lines = _currentCalibration->getTactLines(_currentTact);
    if(!lines.empty()) {
        for(int i=0; i<lines.size(); i++) {
            emit drawAscan(_device->getAscanForLine(lines[i].first));
        }
    }
}

void Core::aScanSingle()
{
    std::vector< std::pair<uint8_t, uint8_t> > lines = _currentCalibration->getTactLines(_currentTact);
    if(!lines.empty()) {
        for(int i=0; i<lines.size(); i++) {
            if(_targetChannel.load() == lines[i].second) {
                emit drawAscan(_device->getAscanForLine(lines[i].first));
            }
        }
    }
}


void Core::process()
{
    // modify state
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
    if(_snapshotRequested.load()) {
        _snapshot = _currentCalibration->getSnapshot();
        _snapshotRequested.store(false);
    }
}

void Core::finish()
{
    qDebug() << "Disconnected!";
}

void Core::evaluationWork()
{
    snapshot();
    check();
    trigger();
    aScanSingle();
    process();
    sync();
}

void Core::searchWork()
{
    snapshot();
    check();
    trigger();
    aScanAll();
    process();
    sync();
}

void Core::notifyTVG(TVG & tvg)
{
    emit drawTVG(tvg);
}

void Core::setDeviceMode(uint8_t mode)
{
    _deviceMode.store(mode);
}

void Core::setChannelBaseSens(int channel, int value)
{
    TVGSimpleModificator * mod = new TVGSimpleModificator(channel, value);

    _changesMutex->lock();
    _pendingChanges.push(mod);
    _changesMutex->unlock();
}

void Core::setTvgCurve(std::vector<uint8_t> points)
{

}

void Core::setSingleChannel(uint8_t channel)
{
    qDebug() << "Setting channel:" <<channel;
    _targetChannel.store(channel);
    //emit channelChanged(channel);
}

