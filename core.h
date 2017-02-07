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
    Q_OBJECT
private:
    std::atomic_bool _active;
    Device * _device;
    DeviceState * _state;
public:
    Core();
    ~Core();
    void run();
private:
    void init();
    void check();
    void ascan();
    void process();
    void sync();
    void finish();
    void work();

signals:
    void drawAscan(AScan scan);
    void debug(int);
    void connectionStatusChanged(bool);
    void errorStatusChanged(bool);
};

#endif // CORE_H
