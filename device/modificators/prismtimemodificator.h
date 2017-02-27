#ifndef PRISMTIMEMODIFICATOR_H
#define PRISMTIMEMODIFICATOR_H

#include "core.h"

class PrismTimeModificator : public Modificator
{
    uint8_t _value;
    ChannelID _channel;
public:
    PrismTimeModificator(ChannelID channel, uint8_t ms);
    void apply(Core * core);
};

#endif // PRISMTIMEMODIFICATOR_H
