#ifndef TVGCURVE_H
#define TVGCURVE_H

#include <vector>

class TVGCurve
{
public:
    TVGCurve();
    virtual TVGCurve * clone() const = 0;
    virtual ~TVGCurve();
    virtual double getSample(double x) = 0;
    virtual std::vector< std::pair< double, double > > getReferencePoints() = 0;
};

#endif // TVGCURVE_H
