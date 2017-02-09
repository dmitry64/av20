#ifndef TVGSIMPLEMODIFICATOR_H
#define TVGSIMPLEMODIFICATOR_H

#include "modificator.h"

class TVGSimpleModificator : public Modificator
{
    int _value;
    int _channel;

public:
    TVGSimpleModificator(int channel, int value);
    void apply(Core *core);
};

#endif // TVGSIMPLEMODIFICATOR_H
