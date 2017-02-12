#ifndef ADDGATEMODIFICATOR_H
#define ADDGATEMODIFICATOR_H

#include "device/modificators/modificator.h"
#include "core.h"

class AddGateModificator : public Modificator
{
    Gate _gate;
    uint8_t _channel;
public:
    AddGateModificator(uint8_t channel, Gate gate);
    void apply(Core * core);
};

#endif // ADDGATEMODIFICATOR_H
