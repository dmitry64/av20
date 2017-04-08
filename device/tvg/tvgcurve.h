#ifndef TVGCURVE_H
#define TVGCURVE_H

#include <vector>
#include "common/definitions.h"

#include <QDomElement>

class TVGCurve
{
public:
    TVGCurve();
    virtual TVGCurve * clone() const = 0;
    virtual ~TVGCurve();
    virtual double getSample(double x) const = 0;
    virtual std::vector< std::pair< double, double > > getReferencePoints() const = 0;
    virtual TVGType getType() const = 0;
    virtual QDomElement generateXML(QDomDocument &doc) = 0;
};

#endif // TVGCURVE_H
