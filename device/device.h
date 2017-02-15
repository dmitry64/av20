#ifndef DEVICE_H
#define DEVICE_H

#include "spi/deviceinterface.h"
#include "spi/driverspi.h"
#include "spi/fakespi.h"
#include "devicestate.h"
#include <vector>
#include "devicemode.h"

class Device
{
    DeviceInterface * _spi;
    DeviceState * _state;

private:
    TactRegisters getRegistersByTact(uint8_t index, DeviceMode *mode);

public:
    Device(DeviceState * state);
    void init();
    void fillRegisters();
    void resetConfigRegisters();
    void resetTVG();
    void resetChannelsTable();
    void applyCalibration(DeviceMode * calibration);
    void setProgTrigger(bool enabled);
    DeviceStatus getDeviceStatus();
    void setTVG(int chIndex, TVG tvg);
    AScan getAscanForLine(uint8_t activeChannel, AScan * output);
    uint8_t getVersion();

    bool checkConnection();
    bool getErrorFlag() const;
};

#endif // DEVICE_H
