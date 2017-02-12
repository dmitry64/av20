#ifndef MODIFICATOR_H
#define MODIFICATOR_H

#include "device/device.h"

class Core;

class Modificator
{
public:
    Modificator();
    virtual ~Modificator();
    virtual void apply(Core * core) = 0;
};

#endif // MODIFICATOR_H
