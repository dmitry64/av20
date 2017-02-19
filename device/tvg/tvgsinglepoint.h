#ifndef TVGSINGLEPOINT_H
#define TVGSINGLEPOINT_H

#include "tvgcurve.h"

class TVGSinglePoint : public TVGCurve
{
    double _xOffset;
    double _yHeight;
public:
    TVGSinglePoint(double offset, double height);
    virtual TVGSinglePoint * clone() const;
    double getSample(double x);
    std::vector< std::pair< double, double > > getReferencePoints();
    TVGType getType();
    double getXOffset() const;
    double getYHeight() const;
};

#endif // TVGSINGLEPOINT_H
