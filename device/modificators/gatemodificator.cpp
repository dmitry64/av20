#include "gatemodificator.h"

GateModificator::GateModificator(ChannelsInfo info, Gate gate)
{
    _gate = gate;
    _info = info;
}

void GateModificator::apply(Core *core)
{
    /*std::vector<Gate> gates = core->getCalibration()->getChannel(_channel)->rx()->gates();

    for(size_t i=0; i<gates.size(); i++) {
        if(gates[i]._id == _gate._id) {
            gates[i]._start = _gate._start;
            gates[i]._finish = _gate._finish;
            gates[i]._level = _gate._level;
        }
    }

    core->getCalibration()->getChannel(_channel)->rx()->setGates(gates);

    core->notifyChannel((core->getCalibration()->getChannel(_channel)));*/
}
