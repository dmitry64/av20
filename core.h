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
    // Atomic flags
    std::atomic_bool _active;
    std::atomic_bool _calibrationSnapshotRequested;
    std::atomic_bool _tactTableSnapshotRequested;
    std::atomic_bool _calibrationsInfoSnapshotRequested;
    std::atomic_bool _modeswitchRequested;
    std::atomic_bool _calibrationSwitchRequested;
    std::atomic_bool _channelSwitchRequested;

    // Mode switch values
    DeviceModeIndex _requestedMode;
    SchemeIndex _requestedScheme;
    CalibrationIndex _requestedCalibration;
    ChannelsInfo _requestedChannelSelection;

    // Tact control
    uint8_t _currentTactCounter;
    uint8_t _currentTact;

    // Core objects
    Device * _device;
    ModeManager * _modeManager;
    CalibrationManager * _calibrationManager;

    // Internal state
    bool _deviceOverheat;
    bool _deviceError;
    bool _deviceConnectionError;
    std::atomic<SchemeIndex> _currentScheme;
    std::atomic<CalibrationIndex> _currentCalibration;
    std::atomic<DeviceModeIndex> _currentMode;

    // Snapshots
    ChannelsCalibration _calibrationsSnapshot;
    CalibrationsInfoList _calibrationsInfoListSnapshot;
    TactTable _tactTableSnapshot;

    // Sync stuff
    QMutex * _changesMutex;
    std::queue<Modificator *> _pendingChanges;

    AScan * _line1CurrentAscan;
    AScan * _line2CurrentAscan;
public:
    Core(ModeManager * modeManager, CalibrationManager * calibrationManager);
    ~Core();

    // System
    void run();
    void stopCore();

    // Internal
    ChannelsCalibration getCalibration();
    void notifyChannel(Channel channel);
    void applyChannelsModification(ChannelID index, Channel channel);

    void applyCurrentCalibrationToDevice();
    const ModeManager *getModeManager() const;


    // External
    ChannelsCalibration getCalibrationsSnapshot();
    CalibrationsInfoList getAvailableCalibrationsSnapshot();
    TactTable getTactTableSnapshot();

private:
    void init();
    void check();
    void trigger();
    void status();
    void process();
    void aScanAll(const std::vector<uint8_t> & lines);
    void aScanProcess(uint8_t line);
    void sync();
    void snapshot();
    void modeswitch();
    void finish();
    void searchWork();

    void addModificator(Modificator *mod);
    void handleDeviceError(bool status);
    void handleDeviceOverheat(bool status);
    void handleDeviceConnectionError(bool status);
    void handleChannelSelection(const ChannelsInfo info);

    TactTable getTactTable();
    DeviceMode getCurrentDeviceMode();

public:
    void addGate(const ChannelsInfo info, const Gate & gate);
    void modifyGate(const ChannelsInfo info, const Gate & gate);
    void removeGate(const ChannelsInfo info, const uint8_t id);
    void setPrismTime(const ChannelsInfo info, const uint8_t value);
    void setTVG(const ChannelsInfo info, const TVGCurve * ptr);
    void setDeviceMode(const DeviceModeIndex modeIndex, const SchemeIndex schemeIndex);
    void switchCalibration(const CalibrationIndex index);
    void switchChannel(const ChannelsInfo info);



    SchemeIndex  getCurrentScheme() const;
    DeviceModeIndex getCurrentMode() const;
    CalibrationIndex getCurrentCalibration() const;
signals:
    void drawDisplayPackage(QSharedPointer<DisplayPackage> package);
    void channelChanged(Channel channel);
    void modeChanged();
    void calibrationChanged();

    void deviceErrorEnable();
    void deviceErrorDisable();

    void deviceOverheatEnable();
    void deviceOverheatDisable();

    void deviceConnectionErrorEnable();
    void deviceConnectionErrorDisable();
};

#endif // CORE_H
