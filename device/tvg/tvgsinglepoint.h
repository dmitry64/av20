#ifndef TVGSINGLEPOINT_H
#define TVGSINGLEPOINT_H

#include "tvgcurve.h"

class TVGSinglePoint : public TVGCurve
{
    double _yBase;
    double _xOffset;
    double _yHeight;
    double _xWidth;
    double _curve;
public:
    TVGSinglePoint(double base, double offset, double width, double height, double curve);
    virtual TVGSinglePoint * clone() const;
    double getSample(double x) const;
    std::vector< std::pair< double, double > > getReferencePoints();
    TVGType getType() const;
    double getXOffset() const;
    double getYHeight() const;
    double getYBase() const;
    double getXWidth() const;
    double getCurve() const;
};

#endif // TVGSINGLEPOINT_H
