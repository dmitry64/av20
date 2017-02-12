#ifndef GATEMODIFICATOR_H
#define GATEMODIFICATOR_H

#include "device/definitions.h"
#include "modificator.h"
#include "core.h"

class GateModificator : public Modificator
{
    Gate _gate;
    uint8_t _channel;
public:
    GateModificator(uint8_t channel, Gate gate);
    void apply(Core * core);
};

#endif // GATEMODIFICATOR_H
