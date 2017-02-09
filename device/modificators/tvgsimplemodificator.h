#ifndef TVGSIMPLEMODIFICATOR_H
#define TVGSIMPLEMODIFICATOR_H

#include "modificator.h"

class TVGSimpleModificator : public Modificator
{
    int _value;
    int _channel;
    TVG _tvg;
public:
    TVGSimpleModificator(int channel, int value);
    void apply(Device *device);
    void notify(Core *core);
};

#endif // TVGSIMPLEMODIFICATOR_H
