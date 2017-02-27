#ifndef ADDGATEMODIFICATOR_H
#define ADDGATEMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class AddGateModificator : public Modificator
{
    Gate _gate;
    ChannelID _channel;
public:
    AddGateModificator(ChannelID channel, Gate gate);
    void apply(Core * core);
};

#endif // ADDGATEMODIFICATOR_H
