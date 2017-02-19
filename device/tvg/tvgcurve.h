#ifndef TVGCURVE_H
#define TVGCURVE_H

#include <vector>
#include "device/definitions.h"

class TVGCurve
{
public:
    TVGCurve();
    virtual TVGCurve * clone() const = 0;
    virtual ~TVGCurve();
    virtual double getSample(double x) = 0;
    virtual std::vector< std::pair< double, double > > getReferencePoints() = 0;
    virtual TVGType getType() = 0;
};

#endif // TVGCURVE_H
