#ifndef CORE_H
#define CORE_H

#include <QThread>
#include <QApplication>
#include <atomic>
#include <queue>
#include "device/modificators/modificator.h"
#include "device/definitions.h"
#include "device/devicecalibration.h"
#include "device/devicestate.h"
#include "device/device.h"
#include <QMutex>

class Core : public QThread
{
    Q_OBJECT
private:
    std::atomic_bool _active;
    std::atomic_uchar _deviceMode;
    std::atomic_bool _snapshotRequested;
    std::atomic_uchar _targetChannel;


    uint8_t _currentTactCounter;
    uint8_t _currentTact;

    Device * _device;
    DeviceState * _state;
    DeviceCalibration * _currentCalibration;
    DeviceCalibration * _snapshot;
    QMutex * _changesMutex;
    std::queue<Modificator *> _pendingChanges;


public:
    Core();
    ~Core();
    void run();
    DeviceCalibration *getCalibration();
    DeviceCalibration *getSnapshot();

    void notifyTVG(TVG &tvg);

private:
    void init();
    void check();
    void trigger();
    void status();
    void aScanAll();
    void aScanSingle();
    void process();
    void sync();
    void snapshot();
    void finish();
    void evaluationWork();
    void searchWork();

public:
    void setDeviceMode(uint8_t mode);
    void setChannelBaseSens(int channel, int value);
    void setTvgCurve(std::vector<uint8_t> points);
    void setSingleChannel(uint8_t channel);

    Device *getDevice() const;

signals:
    void drawAscan(AScan scan);
    void drawTVG(TVG tvg);
    //void channelChanged(uint8_t channel);
    void debug(int);
    void connection(bool);
    void connectionError(bool);
    void deviceError(bool);
    void deviceOverheat(bool);
    void deviceReady(bool);
};

#endif // CORE_H
