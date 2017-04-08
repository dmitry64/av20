#ifndef TVGTWOPOINTS_H
#define TVGTWOPOINTS_H

#include "tvgcurve.h"

class TVGTwoPoints : public TVGCurve
{
    double _yBase;
    double _xOffset;
    double _yHeight;
    double _xWidth;
    double _curve;
public:
    TVGTwoPoints(double base, double offset, double width, double height, double curve);
    explicit TVGTwoPoints(const TVGTwoPoints & original);
    ~TVGTwoPoints();

    double getXOffset() const;
    double getYHeight() const;
    double getYBase() const;
    double getXWidth() const;
    double getCurve() const;

    // TVGCurve interface
public:
    double getSample(double x) const;
    std::vector< std::pair< double, double > > getReferencePoints() const;
    virtual TVGCurve * clone() const;
    QDomElement generateXML(QDomDocument &doc);
    TVGType getType() const;
};

#endif // TVGTWOPOINTS_H
