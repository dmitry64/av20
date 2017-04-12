#ifndef CORE_H
#define CORE_H

#include <QThread>
#include <QApplication>
#include <QSharedPointer>
#include <atomic>
#include <queue>
#include "device/modificators/modificator.h"
#include "common/definitions.h"
#include "device/channelscalibration.h"
#include "device/devicestate.h"
#include "device/device.h"
#include "device/tact/tacttable.h"
#include "device/modemanager.h"
#include "device/calibrationmanager.h"
#include <QMutex>

class Core : public QObject
{
    Q_OBJECT
private:
    // Atomic flags
    std::atomic_bool _active;
    std::atomic_bool _finished;
    std::atomic_bool _calibrationSnapshotRequested;
    std::atomic_bool _tactTableSnapshotRequested;
    std::atomic_bool _calibrationsInfoSnapshotRequested;
    std::atomic_bool _modeswitchRequested;
    std::atomic_bool _calibrationSwitchRequested;
    std::atomic_bool _channelSwitchRequested;
    std::atomic_bool _registrationRequested;

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
    uint8_t _deviceVersion;
    bool _deviceOverheat;
    bool _deviceError;
    bool _deviceConnectionError;
    bool _registrationState;
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

    QString _registrationOutputPath;
    QFile * _registrationFileHandle;

public slots:
    // System
    void work();
    void stopCore();
public:
    Core(ModeManager * modeManager, CalibrationManager * calibrationManager);
    ~Core();

    // Internal
    ChannelsCalibration getCalibration();
    void notifyChannel(const Channel &channel);
    void notifyCalibration();
    void applyChannelsModification(ChannelID index, Channel channel);

    void applyCurrentCalibrationToDevice();
    const ModeManager *getModeManager() const;
    CalibrationManager *getCalibrationManager() const;

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
    void registration();

    void addModificator(Modificator *mod);
    void handleDeviceError(bool status);
    void handleDeviceOverheat(bool status);
    void handleDeviceConnectionError(bool status);
    void handleChannelSelection(const ChannelsInfo &info);

    TactTable getTactTable();
    DeviceMode getCurrentDeviceMode();

public:
    void addGate(const ChannelsInfo &info, const Gate & gate);
    void modifyGate(const ChannelsInfo &info, const Gate & gate);
    void removeGate(const ChannelsInfo &info, const uint8_t id);
    void setPrismTime(const ChannelsInfo &info, const uint8_t value);
    void setPulserFreq(const ChannelsInfo &info, const PulserFreq value);
    void setPulserProg(const ChannelsInfo &info, const PulserProg value);
    void setTVG(const ChannelsInfo &info, const TVGCurve * ptr);
    void setDeviceMode(const DeviceModeIndex modeIndex, const SchemeIndex schemeIndex);
    void switchCalibration(const CalibrationIndex index);
    void switchChannel(const ChannelsInfo &info);
    void createCalibration(const CalibrationIndex baseIndex, const QString &name);
    void removeCalibration(const CalibrationIndex index);

    void startRegistration(const QString &outputFile);
    void stopRegistration();

    SchemeIndex  getCurrentScheme() const;
    DeviceModeIndex getCurrentMode() const;
    CalibrationIndex getCurrentCalibration() const;


signals:
    void displayVersion(QString version);
    void drawDisplayPackage(QSharedPointer<DisplayPackage> package);
    void channelChanged(Channel channel);
    void modeChanged();
    void calibrationChanged();

    void registrationStateChanged(bool);

    void deviceErrorEnable();
    void deviceErrorDisable();

    void deviceOverheatEnable();
    void deviceOverheatDisable();

    void deviceConnectionErrorEnable();
    void deviceConnectionErrorDisable();

    void finished();
};

#endif // CORE_H
