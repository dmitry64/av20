#ifndef DEVICE_H
#define DEVICE_H

#include "spi/driverspi.h"
#include "devicestate.h"
#include <vector>

class Device
{
    DriverSPI * _spi;
    DeviceState * _state;

public:
    Device(DeviceState * state);
    void init();
    void fillRegisters();
    void resetConfigRegisters();
    void resetTVG();
    void resetChannelsTable();
    void setProgTrigger(bool enabled);
    DeviceStatus getDeviceStatus();
    void setTVG(int chIndex, TVG tvg);
    AScan getAscanForChannel(uint8_t activeChannel);
    uint8_t getVersion();


    bool checkConnection();
    bool getErrorFlag() const;
};

#endif // DEVICE_H
