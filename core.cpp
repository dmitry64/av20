#include "core.h"
#include <QDebug>

DeviceState *Core::state() const
{
    return _state;
}

Core::Core() : _active(true), _state(new DeviceState())
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
        work();
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
    emit connectionStatusChanged(_device->checkConnection());
    emit errorStatusChanged(_device->getErrorFlag());
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



    // apply from ui
}

void Core::finish()
{
    qDebug() << "Disconnected!";
}

void Core::work()
{
    static int counter = 0;
    check();
    ascan();
    process();
    sync();
    QApplication::processEvents();
    counter++;
    emit debug(counter);
}

void setBit(uint8_t * ptr, int bit, uint8_t val) {
    uint8_t prev = ptr[bit/8];
    ptr[bit/8] |= (((prev >> (bit % 8)) | val) << (bit % 8));
}

void Core::setTvgCurve(int k)
{
    std::vector<uint8_t> samples;
    for(int i=0; i<TVG_SAMPLES_SIZE; i++) {
        uint8_t sample = std::min(32, i);
        samples.push_back(sample);
    }

    uint8_t packedValues[TVG_SAMPLES_BYTES];
    memset(packedValues,0,TVG_SAMPLES_BYTES);
    for(int i=0; i<samples.size(); i++) {
        for(int j=0; j<6; j++) {
            setBit(packedValues,i*6 + j, (samples[i] >> j) & 0b00000001);
        }
    }

    TVG tvg;
    for(int i=0; i<TVG_SAMPLES_BYTES; i++) {
        tvg._samples[i] = packedValues[i];
    }

    emit drawTVG(tvg);
}

