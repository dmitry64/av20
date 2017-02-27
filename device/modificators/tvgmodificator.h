#ifndef TVGMODIFICATOR_H
#define TVGMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class TVGModificator : public Modificator
{
    ChannelID _channel;
    TVGCurve * _curve;
public:
    TVGModificator(ChannelID channel, TVGCurve * curve);
    void apply(Core * core);
};

#endif // TVGMODIFICATOR_H
