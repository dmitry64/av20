#include "addgatemodificator.h"

AddGateModificator::AddGateModificator(const ChannelsInfo &info, const Gate &gate) : _gate(gate), _info(info)
{

}

void AddGateModificator::apply(Core *core)
{
    auto calibration = core->getCalibration();
    auto channel = calibration.getChannel(_info._channel);
    auto displayChannels = channel.getDisplayChannels();
    auto display = displayChannels[_info._displayChannel];
    auto gates = display.gates();
    uint8_t id = 0;
    for(auto it=gates.begin(); it!=gates.end(); it++) {
        Gate & gate = it.operator*();
        gate._id = id;
        id++;
    }
    _gate._id = gates.size() + 1;
    qDebug() << "Adding gate" <<_gate._id;
    gates.push_back(_gate);
    std::sort(gates.begin(),gates.end(),gateSorter);
    display.setGates(gates);
    displayChannels[_info._displayChannel] = display;
    channel.setDisplayChannels(displayChannels);

    core->applyChannelsModification(_info._channel,channel);
    core->notifyChannel(channel);
}
