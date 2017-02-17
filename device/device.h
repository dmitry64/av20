#ifndef DEVICE_H
#define DEVICE_H

#include "spi/deviceinterface.h"
#include "spi/driverspi.h"
#include "spi/fakespi.h"
#include "devicestate.h"
#include <vector>
#include "channelscalibration.h"
#include "tvg/tvgcurve.h"

class Device
{
    DeviceInterface * _spi;
private:
    TactRegisters getRegistersByTact(uint8_t index, ChannelsCalibration *mode, TactTable *tactTable);
    TVG getTVGFromCurve(TVGCurve * curve);
    void setBit(uint8_t * ptr, int bit, uint8_t val);
public:
    Device();
    void init();
    void fillRegisters();
    void resetConfigRegisters();
    void resetTVG();
    void resetChannelsTable();
    void resetDevice();
    void applyCalibration(ChannelsCalibration * calibration, TactTable * tactTable);
    void setProgTrigger(bool enabled);
    DeviceStatus getDeviceStatus();
    void setTVG(int chIndex, TVG tvg);
    AScan getAscanForLine(uint8_t activeChannel, AScan * output);
    uint8_t getVersion();

    bool checkConnection();
    bool getErrorFlag() const;
};

#endif // DEVICE_H
