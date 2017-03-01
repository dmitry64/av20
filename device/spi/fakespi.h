#ifndef FAKESPI_H
#define FAKESPI_H

#include <stdint.h>
#include <QThread>
#include <atomic>
#include <vector>
#include "device/commonfunctions.h"
#include "device/devicestate.h"
#include "deviceinterface.h"

class FakeSPI : public DeviceInterface, public QThread
{
    DeviceState _state;

    std::vector<std::atomic_int*> _counters;

    uint8_t _currentTact;

    uint8_t _specialCounter;
private:
    uint8_t getNextTact();
    void updateCounters();
    void setAScanForLine1(uint8_t * dest);
    void setAScanForLine2(uint8_t * dest);
    void run();
public:
    FakeSPI();
    void init();
    void getRegister(uint8_t reg, uint32_t length, uint8_t * dest);
    void setRegister(uint8_t reg, const uint32_t length, uint8_t * src);
    bool setAndTestRegister(uint8_t reg, const uint32_t length, uint8_t * src);
    bool getErrorFlag() const;
};

#endif // FAKESPI_H
