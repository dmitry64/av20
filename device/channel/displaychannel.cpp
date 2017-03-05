#include "displaychannel.h"
#include "device/tvg/tvgsinglepoint.h"

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

RxChannel DisplayChannel::getRx() const
{
    return _rx;
}

void DisplayChannel::setRx(const RxChannel &rx)
{
    _rx = rx;
}

TxChannel DisplayChannel::getTx() const
{
    return _tx;
}

void DisplayChannel::setTx(const TxChannel &tx)
{
    _tx = tx;
}

DisplayChannel::DisplayChannel() : _angle(0)
{

}

DisplayChannel::~DisplayChannel()
{
    _gates.clear();
}
