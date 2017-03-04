#ifndef REMOVEGATEMODIFICATOR_H
#define REMOVEGATEMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class RemoveGateModificator : public Modificator
{
    ChannelsInfo _info;
    GateID _gateId;
public:
    RemoveGateModificator(ChannelsInfo info, GateID gateId);
    void apply(Core *core);
};

#endif // REMOVEGATEMODIFICATOR_H
