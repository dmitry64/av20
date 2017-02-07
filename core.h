#ifndef CORE_H
#define CORE_H

#include <QThread>
#include <atomic>
#include <queue>
#include "device/definitions.h"
#include "device/devicestate.h"
#include "device/device.h"

class Core : public QThread
{
private:
    std::atomic_bool _active;
    Device * _device;
    DeviceState * _state;
public:
    Core();
    ~Core();
    void run();
    uint8_t * getAscanPtr();

private:
    void init();
    void check();
    void ascan();
    void process();
    void sync();
    void finish();
    void work();

};

#endif // CORE_H
