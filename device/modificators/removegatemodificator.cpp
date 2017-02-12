#include "removegatemodificator.h"

RemoveGateModificator::RemoveGateModificator(uint8_t channel, uint8_t gateId)
{
    _channel = channel;
    _gateId = gateId;
}

void RemoveGateModificator::apply(Core *core)
{
    std::vector<Gate> gates = core->getCalibration()->getChannel(_channel)->gates();
    std::vector<Gate> result;
    for(int i=0; i<gates.size(); i++) {
        if(gates[i]._id!=_gateId) {
            result.push_back(gates[i]);
        }
    }
    core->getCalibration()->getChannel(_channel)->setGates(result);
}
