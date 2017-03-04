#ifndef TXCHANNEL_H
#define TXCHANNEL_H

#include "device/definitions.h"

class TxChannel
{
    PulserFreq _freq;
    PulserProg _prog;
    bool _doubleMode;
public:
    TxChannel();
    ~TxChannel();
    PulserFreq freq() const;
    void setFreq(const PulserFreq &freq);
    PulserProg prog() const;
    void setProg(const PulserProg &prog);
    bool doubleMode() const;
    void setDoubleMode(bool doubleMode);
};

#endif // TXCHANNEL_H
