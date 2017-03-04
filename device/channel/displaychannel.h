#ifndef DISPLAYCHANNEL_H
#define DISPLAYCHANNEL_H

#include "device/definitions.h"

class DisplayChannel
{
    std::vector<Gate> _gates;
    double _angle;
public:
    DisplayChannel();
    ~DisplayChannel();
    std::vector<Gate> gates() const;
    void setGates(const std::vector<Gate> &gates);
    double angle() const;
    void setAngle(double angle);
};

#endif // DISPLAYCHANNEL_H
