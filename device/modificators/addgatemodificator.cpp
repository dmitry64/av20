#include "addgatemodificator.h"

AddGateModificator::AddGateModificator(ChannelID channel, Gate gate)
{
    _gate = gate;
    _channel = channel;
}

void AddGateModificator::apply(Core *core)
{
    std::vector<Gate> gates = core->getCalibration()->getChannel(_channel)->rx()->gates();
    gates.push_back(_gate);
    core->getCalibration()->getChannel(_channel)->rx()->setGates(gates);
    core->notifyChannel((core->getCalibration()->getChannel(_channel)));
}
