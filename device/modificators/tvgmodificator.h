#ifndef TVGMODIFICATOR_H
#define TVGMODIFICATOR_H

#include "modificator.h"
#include "core.h"

class TVGModificator : public Modificator
{
    uint8_t _channel;
    TVGCurve * _curve;
public:
    TVGModificator(uint8_t channel, TVGCurve * curve);
    void apply(Core * core);
};

#endif // TVGMODIFICATOR_H
