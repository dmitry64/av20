#ifndef PULSERFREQMODIFICATOR_H
#define PULSERFREQMODIFICATOR_H

#include "modificator.h"
#include "core.h"
#include "common/definitions.h"

class PulserFreqModificator : public Modificator
{
    ChannelsInfo _info;
    PulserFreq _freq;

public:
    PulserFreqModificator(const ChannelsInfo &info, PulserFreq value);

    // Modificator interface
public:
    void apply(Core *core);
};

#endif // PULSERFREQMODIFICATOR_H
