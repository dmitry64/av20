#ifndef REMOVEGATEMODIFICATOR_H
#define REMOVEGATEMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class RemoveGateModificator : public Modificator
{
    uint8_t _channel;
    uint8_t _gateId;
public:
    RemoveGateModificator(uint8_t channel, uint8_t gateId);
    void apply(Core *core);
};

#endif // REMOVEGATEMODIFICATOR_H
