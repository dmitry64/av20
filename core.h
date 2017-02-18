#ifndef CORE_H
#define CORE_H

#include <QThread>
#include <QApplication>
#include <QSharedPointer>
#include <atomic>
#include <queue>
#include "device/modificators/modificator.h"
#include "device/definitions.h"
#include "device/channelscalibration.h"
#include "device/devicestate.h"
#include "device/device.h"
#include "device/tact/tacttable.h"
#include "device/modemanager.h"
#include "device/calibrationmanager.h"
#include <QMutex>

class Core : public QThread
{
    Q_OBJECT
private:
    std::atomic_bool _active;
    std::atomic_bool _calibrationSnapshotRequested;
    std::atomic_bool _tactTableSnapshotRequested;
    std::atomic_bool _modeswitchRequested;

    uint8_t _requestedMode;
    uint8_t _requestedScheme;

    uint8_t _currentTactCounter;
    uint8_t _currentTact;

    Device * _device;
   // DeviceState * _state;

    ModeManager * _modeManager;
    CalibrationManager * _calibrationManager;

    ChannelsCalibration * _currentCalibration;
    ChannelsCalibration * _calibrationsSnapshot;

    DeviceMode * _currentMode;

    //TactTable * _tactTable;
    uint8_t _currentScheme;
    TactTable * _tactTableSnapshot;

    QMutex * _changesMutex;
    std::queue<Modificator *> _pendingChanges;

    bool _deviceOverheat;
    bool _deviceError;
    bool _deviceConnectionError;

    AScan * _line1CurrentAscan;
    AScan * _line2CurrentAscan;

public:
    Core(ModeManager * modeManager, CalibrationManager * calibrationManager);
    ~Core();
    void run();
    void stopCore();
    ChannelsCalibration *getCalibration();
    ChannelsCalibration *getCalibrationsSnapshot();

    TactTable *getTactTableSnapshot();

    void notifyChannel(Channel channel);
    void applyCurrentCalibrationToDevice();

private:
    void init();
    void check();
    void trigger();
    void status();
    void aScanAll();
    void process();
    void sync();
    void snapshot();
    void modeswitch();
    void finish();
    void searchWork();

    void addModificator(Modificator * mod);
    void handleDeviceError(bool status);
    void handleDeviceOverheat(bool status);
    void handleDeviceConnectionError(bool status);

    TactTable *getTactTable();

public:
    void addGate(uint8_t channel, Gate gate);
    void modifyGate(uint8_t channel, Gate gate);
    void removeGate(uint8_t channel, uint8_t id);
    void setPrismTime(uint8_t channel, uint8_t value);
    void setDeviceMode(uint8_t modeIndex, uint8_t schemeIndex);

    Device *getDevice() const;

    ModeManager *getModeManager() const;

signals:
    //void drawAscan(QSharedPointer<AScanDrawData> scan);
    //void drawBscan(QSharedPointer<BScanDrawData> scan);
    void drawDisplayPackage(QSharedPointer<DisplayPackage> package);
    //void drawTVG(TVG tvg);
    void channelChanged(Channel channel);

    void deviceErrorEnable();
    void deviceErrorDisable();

    void deviceOverheatEnable();
    void deviceOverheatDisable();

    void deviceConnectionErrorEnable();
    void deviceConnectionErrorDisable();
};

#endif // CORE_H
