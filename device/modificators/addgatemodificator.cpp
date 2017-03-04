#include "addgatemodificator.h"

AddGateModificator::AddGateModificator(ChannelsInfo info, Gate gate)
{
    _gate = gate;
    _info = info;
}

void AddGateModificator::apply(Core *core)
{
    /*std::vector<Gate> gates = core->getCalibration()->getChannel(_channel)->rx()->gates();
    gates.push_back(_gate);
    core->getCalibration()->getChannel(_channel)->rx()->setGates(gates);
    core->notifyChannel((core->getCalibration()->getChannel(_channel)));*/
}
