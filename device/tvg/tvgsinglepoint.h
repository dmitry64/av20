#ifndef TVGSINGLEPOINT_H
#define TVGSINGLEPOINT_H

#include "device/tvgcurve.h"

class TVGSinglePoint : public TVGCurve
{
    double _xOffset;
public:
    TVGSinglePoint(double offset);
    double getSample(double x);
};

#endif // TVGSINGLEPOINT_H
