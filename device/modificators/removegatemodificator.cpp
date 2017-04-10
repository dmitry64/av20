#include "removegatemodificator.h"

RemoveGateModificator::RemoveGateModificator(const ChannelsInfo &info, GateID gateId) : _info(info), _gateId(gateId)
{
}

void RemoveGateModificator::apply(Core *core)
{
    auto calibration = core->getCalibration();
    auto channel = calibration.getChannel(_info._channel);
    auto displayChannels = channel.getDisplayChannels();
    auto display = displayChannels[_info._displayChannel];
    auto gates = display.gates();
    std::vector<Gate> result;
    uint8_t id = 0;
    for(size_t i=0; i<gates.size(); i++) {
        if(gates[i]._id!=_gateId) {
            gates[i]._id = id;
            result.push_back(gates[i]);
            id++;
        }
    }
    std::sort(result.begin(),result.end(),gateSorter);
    display.setGates(result);
    displayChannels[_info._displayChannel] = display;
    channel.setDisplayChannels(displayChannels);

    core->applyChannelsModification(_info._channel,channel);
    core->notifyChannel(channel);
}
