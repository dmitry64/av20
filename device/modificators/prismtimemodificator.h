#ifndef PRISMTIMEMODIFICATOR_H
#define PRISMTIMEMODIFICATOR_H

#include "core.h"

class PrismTimeModificator : public Modificator
{
    uint8_t _value;
    ChannelsInfo _info;
public:
    PrismTimeModificator(const ChannelsInfo & info, uint8_t ms);
    void apply(Core * core);
};

#endif // PRISMTIMEMODIFICATOR_H
