#ifndef GATEMODIFICATOR_H
#define GATEMODIFICATOR_H

#include "device/definitions.h"
#include "modificator.h"
#include "core.h"

class GateModificator : public Modificator
{
    Gate _gate;
    ChannelID _channel;
public:
    GateModificator(ChannelID channel, Gate gate);
    void apply(Core * core);
};

#endif // GATEMODIFICATOR_H
