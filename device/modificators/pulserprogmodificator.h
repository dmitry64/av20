#ifndef PULSERPROGMODIFICATOR_H
#define PULSERPROGMODIFICATOR_H


#include "modificator.h"
#include "core.h"
#include "common/definitions.h"

class PulserProgModificator : public Modificator
{
    ChannelsInfo _info;
    PulserProg _prog;

public:
    PulserProgModificator(const ChannelsInfo &info, PulserProg value);

    // Modificator interface
public:
    void apply(Core *core);
};

#endif // PULSERPROGMODIFICATOR_H
