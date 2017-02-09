#ifndef MODIFICATOR_H
#define MODIFICATOR_H

#include "device/device.h"

class Core;

class Modificator
{
public:
    Modificator();
    virtual void apply(Device * device) = 0;
    virtual void notify(Core * core) = 0;
};

#endif // MODIFICATOR_H
