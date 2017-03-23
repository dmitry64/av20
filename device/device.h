#ifndef DEVICE_H
#define DEVICE_H

#include "spi/deviceinterface.h"
#include "spi/driverspi.h"
#include "spi/fakespi.h"
#include "common/commonfunctions.h"
#include <vector>
#include "channelscalibration.h"
#include "tvg/tvgcurve.h"

class Device
{
    DeviceInterface * _spi;
private:
    TactRegisters getRegistersByTact(const uint8_t index, const ChannelsCalibration & mode, const TactTable & tactTable);
    TVG getTVGFromCurve(const TVGCurve *curve) const;
public:
    Device();
    ~Device();
    void init(uint8_t * version);
    void fillRegisters();
    void resetConfigRegisters();
    void resetTVG();
    void resetChannelsTable();
    void resetDevice();
    void applyCalibration(const ChannelsCalibration & calibration, const TactTable & tactTable);
    void setProgTrigger(bool enabled);
    DeviceStatus getDeviceStatus();
    void setTVG(const ChannelID chIndex, const TVG &tvg);
    void setTact(const TactRegisters &reg, const TactIndex index);
    AScan getAscanForLine(const uint8_t line, AScan * output);
    uint8_t getVersion();

    bool checkConnection();
    bool getErrorFlag() const;
};

#endif // DEVICE_H
