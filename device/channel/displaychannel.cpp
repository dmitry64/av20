#include "displaychannel.h"

std::vector<Gate> DisplayChannel::gates() const
{
    return _gates;
}

void DisplayChannel::setGates(const std::vector<Gate> &gates)
{
    _gates = gates;
}

double DisplayChannel::angle() const
{
    return _angle;
}

void DisplayChannel::setAngle(double angle)
{
    _angle = angle;
}

DisplayChannel::DisplayChannel()
{

}

DisplayChannel::~DisplayChannel()
{
    _gates.clear();
}
