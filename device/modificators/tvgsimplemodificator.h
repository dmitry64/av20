#ifndef TVGSIMPLEMODIFICATOR_H
#define TVGSIMPLEMODIFICATOR_H

#include "modificator.h"

class TVGSimpleModificator : public Modificator
{
    TVG _value;
    int _channel;
public:
    TVGSimpleModificator(int channel, TVG &value);
    void apply(Device *device);
};

#endif // TVGSIMPLEMODIFICATOR_H
