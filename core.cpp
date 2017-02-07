#include "core.h"
#include <QDebug>

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

uint8_t *Core::getAscanPtr()
{
    return _state->getAscanForChannel(0);
}

void Core::init()
{
    _device->init();
}

void Core::check()
{
    //emit connectionStatusChanged(_device.checkConnection());
    //emit errorStatusChanged(_device.getErrorFlag());
}

void Core::ascan()
{
    _device->getAscanForChannel(0);
    _device->getAscanForChannel(1);
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
    counter++;
    //emit debug(counter);
}

