#ifndef TVGCURVE_H
#define TVGCURVE_H


class TVGCurve
{
public:
    TVGCurve();
    virtual double getSample(double x) = 0;
};

#endif // TVGCURVE_H
