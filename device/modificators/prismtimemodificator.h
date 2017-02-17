#ifndef PRISMTIMEMODIFICATOR_H
#define PRISMTIMEMODIFICATOR_H

#include "core.h"

class PrismTimeModificator : public Modificator
{
    uint8_t _value;
    uint8_t _channel;
public:
    PrismTimeModificator(uint8_t channel, uint8_t ms);
    void apply(Core * core);
};

#endif // PRISMTIMEMODIFICATOR_H
