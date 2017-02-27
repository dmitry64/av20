#ifndef REMOVEGATEMODIFICATOR_H
#define REMOVEGATEMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class RemoveGateModificator : public Modificator
{
    uint8_t _channel;
    GateID _gateId;
public:
    RemoveGateModificator(ChannelID channel, GateID gateId);
    void apply(Core *core);
};

#endif // REMOVEGATEMODIFICATOR_H
