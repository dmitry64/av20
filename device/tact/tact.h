#ifndef TACT_H
#define TACT_H

#include <stdint.h>
#include <vector>

#include "device/channel/rxchannel.h"
#include "device/definitions.h"

class Tact
{
    bool _tactEnabled;
    bool _diffMode;

    bool _tx1Enabled;
    uint8_t _tx1;
    bool _rx1Enabled;
    uint8_t _rx1;

    bool _tx2Enabled;
    uint8_t _tx2;
    bool _rx2Enabled;
    uint8_t _rx2;

public:
    Tact();

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

    bool getDiffMode() const;
};

#endif // TACT_H
