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

Core::Core() : _active(true), _state(new DeviceState()), _deviceMode(DEVICE_MODE_HAND), _changesMutex(new QMutex())
{
    _device = (new Device(_state));
    _currentCalibration = new DeviceCalibration();
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
        case DEVICE_MODE_HAND:
            handWork();
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
    setTvgCurve(0);
}

void Core::check()
{
    emit connection(_device->checkConnection());
    emit connectionError(_device->getErrorFlag());
}

void Core::trigger()
{
    _device->setProgTrigger(true);
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

void Core::ascan()
{
    emit drawAscan(_device->getAscanForChannel(0));

    //_device->getAscanForChannel(1);
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
            mod->apply(_device);
            mod->notify(this);
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

void Core::handWork()
{
    static int counter = 0;
    snapshot();
    check();
    trigger();
    ascan();
    process();
    sync();
    //QApplication::processEvents();
    counter++;
    emit debug(counter);
}

void Core::notifyTVG(TVG & tvg)
{
    emit drawTVG(tvg);
}

void Core::setDeviceMode(uint8_t mode)
{
    _deviceMode.store(mode);
}


void Core::setTvgCurve(int k)
{
    TVGSimpleModificator * mod = new TVGSimpleModificator(0, k);

    _changesMutex->lock();
    _pendingChanges.push(mod);
    _changesMutex->unlock();
}

void Core::setTvgCurve(std::vector<uint8_t> points)
{

}

