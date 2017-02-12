#include "addgatemodificator.h"

AddGateModificator::AddGateModificator(uint8_t channel, Gate gate)
{
    _gate = gate;
    _channel = channel;
}

void AddGateModificator::apply(Core *core)
{
    std::vector<Gate> gates = core->getCalibration()->getChannel(_channel)->gates();
    gates.push_back(_gate);
    core->getCalibration()->getChannel(_channel)->setGates(gates);
    core->notifyChannel(*(core->getCalibration()->getChannel(_channel)));
}
