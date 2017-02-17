#include "tvgsinglepoint.h"
#include "math.h"
#include <QDebug>

TVGSinglePoint::TVGSinglePoint(double offset) : _xOffset(offset)
{

}

double TVGSinglePoint::getSample(double x)
{
   // return (sin(x * 30) + 1.0)/2.0;
    if(x>0.3) {
        return 1.0;
    } else {
        return std::min(x * 10,1.0);
    }
}
