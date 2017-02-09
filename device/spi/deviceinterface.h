#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include <stdint.h>

class DeviceInterface {
public:
    DeviceInterface()
    {

    }
    virtual void init() = 0;
    virtual void getRegister(uint8_t reg, uint32_t length, uint8_t * dest) = 0;
    virtual void setRegister(uint8_t reg, const uint32_t length, uint8_t * src) = 0;
    virtual bool setAndTestRegister(uint8_t reg, const uint32_t length, uint8_t * src) = 0;
    virtual bool getErrorFlag() const = 0;
};


#endif // DEVICEINTERFACE_H
