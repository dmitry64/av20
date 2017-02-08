#include "core.h"
#include <QDebug>
#include "device/modificators/tvgsimplemodificator.h"

DeviceState *Core::state() const
{
    return _state;
}

Core::Core() : _active(true), _state(new DeviceState()), _deviceMode(DEVICE_MODE_HAND), _changesMutex(new QMutex())
{
    _device = (new Device(_state));

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
        default:
            qFatal("Unknown mode!");
            break;
        }
    }
    finish();
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
            delete mod;
            _pendingChanges.pop();
        }
        _changesMutex->unlock();
    }
    // apply from ui
}

void Core::finish()
{
    qDebug() << "Disconnected!";
}

void Core::handWork()
{
    static int counter = 0;
    check();
    trigger();
    ascan();
    process();
    sync();
    QApplication::processEvents();
    counter++;
    emit debug(counter);
}

void Core::setDeviceMode(uint8_t mode)
{
    _deviceMode.store(mode);
}

void setBit(uint8_t * ptr, int bit, uint8_t val) {
    uint8_t prev = ptr[bit/8];
    ptr[bit/8] |= (((prev >> (bit % 8)) | val) << (bit % 8));
}

void Core::setTvgCurve(int k)
{
    std::vector<uint8_t> samples;
    for(int i=0; i<TVG_SAMPLES_SIZE; i++) {
        uint8_t sample = std::min(127, i + k);
        samples.push_back(sample);
    }

    uint8_t packedValues[TVG_SAMPLES_BYTES];
    memset(packedValues,0,TVG_SAMPLES_BYTES);
    for(int i=0; i<samples.size(); i++) {
        for(int j=0; j<7; j++) {
            setBit(packedValues,i*7 + j, (samples[i] >> j) & 0b00000001);
        }
    }

    TVG tvg;
    for(int i=0; i<TVG_SAMPLES_BYTES; i++) {
        tvg._samples[i] = packedValues[i];
    }

    emit drawTVG(tvg);

    TVGSimpleModificator * mod = new TVGSimpleModificator(0, tvg);

    _changesMutex->lock();
    _pendingChanges.push(mod);
    _changesMutex->unlock();
}

