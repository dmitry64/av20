#ifndef TVGMODIFICATOR_H
#define TVGMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class TVGModificator : public Modificator
{
    ChannelID _channel;
    const TVGCurve * _curve;
public:
    TVGModificator(ChannelID channel, const TVGCurve * curve);
    void apply(Core * core);
};

#endif // TVGMODIFICATOR_H
