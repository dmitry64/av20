#include "gatemodificator.h"

GateModificator::GateModificator(ChannelsInfo info, Gate gate)
{
    _gate = gate;
    _info = info;
}

void GateModificator::apply(Core *core)
{
    auto calibration = core->getCalibration();
    auto channel = calibration.getChannel(_info._channel);
    auto displayChannels = channel.getDisplayChannels();
    auto display = displayChannels[_info._displayChannel];
    auto gates = display.gates();
    for(size_t i=0; i<gates.size(); i++) {
        if(gates[i]._id == _gate._id) {
            gates[i]._start = _gate._start;
            gates[i]._finish = _gate._finish;
            gates[i]._level = _gate._level;
        }
    }
    display.setGates(gates);
    displayChannels[_info._displayChannel] = display;
    channel.setDisplayChannels(displayChannels);

    core->applyChannelsModification(_info._channel,channel);
    core->notifyChannel(channel);
}
