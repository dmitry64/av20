#ifndef ADDGATEMODIFICATOR_H
#define ADDGATEMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class AddGateModificator : public Modificator
{
    Gate _gate;
    ChannelsInfo _info;
public:
    AddGateModificator(const ChannelsInfo &info, const Gate &gate);
    void apply(Core * core);
};

#endif // ADDGATEMODIFICATOR_H
