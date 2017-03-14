#ifndef DRIVERSPI_H
#define DRIVERSPI_H

#include <QString>
#include "deviceinterface.h"

class DriverSPI : public DeviceInterface
{
    QString _device;
    int _deviceFD;

    uint8_t _mode;
    uint8_t _bits;
    uint32_t _speed;
    uint16_t _csdelay;
    uint8_t _cschange;

    bool _errorFlag;
private:
    void sendCommand(uint8_t commandByte, uint8_t length);
    void sendData(uint8_t length, const uint8_t * bufPtr);
    void recvData(uint32_t length, uint8_t * bufPtr);
public:
    explicit DriverSPI(QString & device);
    void init();
    void getRegister(uint8_t reg, const uint32_t length, uint8_t * dest);
    void setRegister(uint8_t reg, const uint32_t length, const uint8_t * src);
    bool setAndTestRegister(uint8_t reg, const uint32_t length, const uint8_t * src);
    bool getErrorFlag() const;
};

#endif // DRIVERSPI_H
