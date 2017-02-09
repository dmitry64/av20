#ifndef ACTIVECHANNELMODIFICATOR_H
#define ACTIVECHANNELMODIFICATOR_H

#include "core.h"

class ActiveChannelModificator : public Modificator
{
public:
    ActiveChannelModificator();
    void apply(Core *core);
};

#endif // ACTIVECHANNELMODIFICATOR_H
