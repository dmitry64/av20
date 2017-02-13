#ifndef TACT_H
#define TACT_H

#include <stdint.h>
#include <vector>

#include "channel.h"
#include "definitions.h"

class Tact
{
    bool _tactEnabled;
    bool _diffMode;

    // First line
    bool _tx1Enabled;
    uint8_t _tx1;
    bool _rx1Enabled;
    uint8_t _rx1;

    bool _double1;
    PulserProg _prog1;
    PulserFreq _freq1;

    // Second line

    bool _tx2Enabled;
    uint8_t _tx2;
    bool _rx2Enabled;
    uint8_t _rx2;

    bool _double2;
    PulserProg _prog2;
    PulserFreq _freq2;

public:
    Tact();
    TactRegisters getRegisters();

    bool getTx1Enabled() const;
    bool getRx1Enabled() const;
    bool getTx2Enabled() const;
    bool getRx2Enabled() const;

    uint8_t getTx1() const;
    uint8_t getRx1() const;
    uint8_t getTx2() const;
    uint8_t getRx2() const;
    void setTx1Enabled(bool tx1Enabled);
    void setRx1Enabled(bool rx1Enabled);
    void setTx2Enabled(bool tx2Enabled);
    void setRx2Enabled(bool rx2Enabled);
    void setTx1(const uint8_t &tx1);
    void setRx1(const uint8_t &rx1);
    void setTx2(const uint8_t &tx2);
    void setRx2(const uint8_t &rx2);
    bool getTactEnabled() const;
    void setTactEnabled(bool tactEnabled);
    PulserProg getProg1() const;
    PulserFreq getFreq1() const;
    PulserProg getProg2() const;
    PulserFreq getFreq2() const;
    void setProg1(const PulserProg &prog1);
    void setFreq1(const PulserFreq &freq1);
    void setProg2(const PulserProg &prog2);
    void setFreq2(const PulserFreq &freq2);
};

#endif // TACT_H
