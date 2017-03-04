#ifndef TVGMODIFICATOR_H
#define TVGMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class TVGModificator : public Modificator
{
    ChannelsInfo _info;
    TVGCurve * _curve;
public:
    TVGModificator(ChannelsInfo info, TVGCurve *curve);
    void apply(Core * core);
};

#endif // TVGMODIFICATOR_H
