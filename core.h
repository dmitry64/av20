#ifndef CORE_H
#define CORE_H

#include <QThread>
#include <QApplication>
#include <atomic>
#include <queue>
#include "device/modificators/modificator.h"
#include "device/definitions.h"
#include "device/devicestate.h"
#include "device/device.h"
#include <QMutex>

class Core : public QThread
{
    Q_OBJECT
private:
    std::atomic_bool _active;
    std::atomic_uchar _deviceMode;
    Device * _device;
    DeviceState * _state;

    QMutex * _changesMutex;
    std::queue<Modificator *> _pendingChanges;
public:
    Core();
    ~Core();
    void run();
    DeviceState *state() const;

private:
    void init();
    void check();
    void trigger();
    void status();
    void ascan();
    void process();
    void sync();
    void finish();
    void handWork();

public:
    void setDeviceMode(uint8_t mode);
    void setTvgCurve(int k);


signals:
    void drawAscan(AScan scan);
    void drawTVG(TVG tvg);
    void debug(int);
    void connection(bool);
    void connectionError(bool);
    void deviceError(bool);
    void deviceOverheat(bool);
    void deviceReady(bool);
};

#endif // CORE_H
