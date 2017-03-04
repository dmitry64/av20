#include "removegatemodificator.h"

RemoveGateModificator::RemoveGateModificator(ChannelsInfo info, GateID gateId)
{
    _info = info;
    _gateId = gateId;
}

void RemoveGateModificator::apply(Core *core)
{
    /*std::vector<Gate> gates = core->getCalibration()->getChannel(_channel)->rx()->gates();
    std::vector<Gate> result;
    for(size_t i=0; i<gates.size(); i++) {
        if(gates[i]._id!=_gateId) {
            result.push_back(gates[i]);
        }
    }
    core->getCalibration()->getChannel(_channel)->rx()->setGates(result);
    core->notifyChannel((core->getCalibration()->getChannel(_channel)));*/
}
