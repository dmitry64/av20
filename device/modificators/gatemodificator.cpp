#include "gatemodificator.h"

GateModificator::GateModificator(uint8_t channel, Gate gate)
{
    _gate = gate;
    _channel = channel;
}

void GateModificator::apply(Core *core)
{
    std::vector<Gate> gates = core->getCalibration()->getChannel(_channel)->gates();

    for(int i=0; i<gates.size(); i++) {
        if(gates[i]._id == _gate._id) {
            gates[i]._start = _gate._start;
            gates[i]._finish = _gate._finish;
            gates[i]._level = _gate._level;
        }
    }

    core->notifyChannel(*(core->getCalibration()->getChannel(_channel)));
}