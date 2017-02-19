#include "tvgsinglepoint.h"
#include "math.h"
#include <QDebug>

TVGSinglePoint::TVGSinglePoint(double offset, double height) : _xOffset(offset), _yHeight(height)
{

}

TVGSinglePoint *TVGSinglePoint::clone() const
{
    return new TVGSinglePoint(*this);
}

double TVGSinglePoint::getSample(double x)
{
   // return (sin(x * 30) + 1.0)/2.0;
    double voff = (_yHeight == 0.0) ? 0.001 : _yHeight;
    double hoff = (_xOffset == 0.0) ? 0.001 : _xOffset;

    double m = voff / hoff;

    return std::min(1.0, std::min(m * x,voff));
    /*if(x>off) {
        return y;
    } else {
        return std::min(x * 10,y);
    }*/
}

std::vector<std::pair<double, double> > TVGSinglePoint::getReferencePoints()
{
    std::vector<std::pair<double, double> > result;
    result.push_back(std::pair<double, double>(_xOffset,_yHeight));
    return result;
}
