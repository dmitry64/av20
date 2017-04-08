#ifndef TVGNPOINTS_H
#define TVGNPOINTS_H

#include "tvgcurve.h"

class TVGNPoints : public TVGCurve
{
    std::vector<std::pair<double, double> > _points;
public:
    TVGNPoints();
    explicit TVGNPoints(const TVGNPoints &original);
    void setPoints(const std::vector<std::pair<double, double> > &points);
    // TVGCurve interface
public:
    TVGCurve *clone() const;
    double getSample(double x) const;
    std::vector<std::pair<double, double> > getReferencePoints() const;
    TVGType getType() const;
    QDomElement generateXML(QDomDocument &doc);

};

#endif // TVGNPOINTS_H
