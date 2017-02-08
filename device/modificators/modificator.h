#ifndef MODIFICATOR_H
#define MODIFICATOR_H
#include "device/device.h"

class Modificator
{
public:
    Modificator();
    virtual void apply(Device * device) = 0;
};

#endif // MODIFICATOR_H
