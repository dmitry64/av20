#ifndef FAKESPI_H
#define FAKESPI_H

#include <stdint.h>
#include <QThread>
#include <atomic>
#include <vector>
#include "common/commonfunctions.h"
#include "device/devicestate.h"
#include "deviceinterface.h"
#include <QElapsedTimer>

class FakeSPI : public DeviceInterface, public QThread
{
    DeviceState _state;
    std::vector<std::atomic_int*> _counters;
    uint8_t _currentTact;
    uint8_t _specialCounter;
    std::atomic_bool _active;
    QElapsedTimer _timer;
private:
    uint8_t getNextTact();
    void updateCounters();
    void setAScanForLine1(uint8_t * dest);
    void setAScanForLine2(uint8_t * dest);
    void run();
    void generateAscan(uint8_t *dest, bool line);

    unsigned char sincFunc(TVG tvg, uint8_t chan, int i, int time);
    unsigned char sinusFunc(TVG tvg, uint8_t chan, int i, int time);
    unsigned char cosinusFunc(TVG tvg, uint8_t chan, int i, int time);

public:
    FakeSPI();
    ~FakeSPI();
    void init();
    void finish();
    void getRegister(uint8_t reg, const uint32_t length, uint8_t * dest);
    void setRegister(uint8_t reg, const uint32_t length, const uint8_t * src);
    bool setAndTestRegister(uint8_t reg, const uint32_t length, const uint8_t * src);
    bool getErrorFlag() const;
};

#endif // FAKESPI_H
