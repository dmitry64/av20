#ifndef TVGMODIFICATOR_H
#define TVGMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class TVGModificator : public Modificator
{
    ChannelsInfo _info;
    TVGCurve * _curve;
public:
    TVGModificator(const ChannelsInfo & info, TVGCurve *curve);
    ~TVGModificator();

    void apply(Core * core);
};

#endif // TVGMODIFICATOR_H
