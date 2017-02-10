#ifndef FAKESPI_H
#define FAKESPI_H

#include <stdint.h>
#include <QThread>
#include "device/devicestate.h"
#include "deviceinterface.h"

class FakeSPI : public DeviceInterface, public QThread
{
    DeviceState _state;
    int _ascanL1Counter;
    int _ascanL1Counter2;
    int _ascanL2Counter;
    int _ascanL2Counter2;
    bool _directionL1;
    bool _directionL2;

    uint8_t _currentTact;

private:
    uint8_t getNextTact();
    void updateCounters();
    void setAScanForLine1(uint8_t * dest);
    void setAScanForLine2(uint8_t * dest);
public:
    FakeSPI();
    void init();
    void getRegister(uint8_t reg, uint32_t length, uint8_t * dest);
    void setRegister(uint8_t reg, const uint32_t length, uint8_t * src);
    bool setAndTestRegister(uint8_t reg, const uint32_t length, uint8_t * src);
    bool getErrorFlag() const;
};

#endif // FAKESPI_H
