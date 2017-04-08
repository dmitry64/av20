#include "tvgtwopoints.h"
#include "math.h"
#include <QDebug>

double TVGTwoPoints::getXOffset() const
{
    return _xOffset;
}

double TVGTwoPoints::getYHeight() const
{
    return _yHeight;
}

double TVGTwoPoints::getYBase() const
{
    return _yBase;
}

double TVGTwoPoints::getXWidth() const
{
    return _xWidth;
}

double TVGTwoPoints::getCurve() const
{
    return _curve;
}

TVGTwoPoints::TVGTwoPoints(double base, double offset, double width, double height, double curve) : _yBase(base), _xOffset(offset), _yHeight(height), _xWidth(width), _curve(curve)
{

}
TVGTwoPoints::TVGTwoPoints(const TVGTwoPoints &original)
{
    _yBase = original._yBase;
    _xOffset = original._xOffset;
    _yHeight = original._yHeight;
    _xWidth = original._xWidth;
    _curve = original._curve;

}
/*
TVGTwoPoints::TVGTwoPoints(const TVGTwoPoints *original)
{
    _yBase = original->_yBase;
    _xOffset = original->_xOffset;
    _yHeight = original->_yHeight;
    _xWidth = original->_xWidth;
    _curve = original->_curve;
}
*/
TVGTwoPoints::~TVGTwoPoints()
{

}

TVGCurve *TVGTwoPoints::clone() const
{
    return new TVGTwoPoints(*this);
}

QDomElement TVGTwoPoints::generateXML(QDomDocument &doc)
{
    QDomElement tvg = doc.createElement("tvg");

    tvg.setAttribute("type","single");

    QDomElement yBase = doc.createElement("yBase");
    yBase.appendChild(doc.createTextNode(QString::number(_yBase)));
    tvg.appendChild(yBase);

    QDomElement xOffset = doc.createElement("xOffset");
    xOffset.appendChild(doc.createTextNode(QString::number(_xOffset)));
    tvg.appendChild(xOffset);

    QDomElement yHeight = doc.createElement("yHeight");
    yHeight.appendChild(doc.createTextNode(QString::number(_yHeight)));
    tvg.appendChild(yHeight);

    QDomElement xWidth = doc.createElement("xWidth");
    xWidth.appendChild(doc.createTextNode(QString::number(_xWidth)));
    tvg.appendChild(xWidth);

    QDomElement curve = doc.createElement("curve");
    curve.appendChild(doc.createTextNode(QString::number(_curve)));
    tvg.appendChild(curve);

    return tvg;
}

double TVGTwoPoints::getSample(double x) const
{
    double Xms = x * 200.0;
    if(Xms<=_xOffset) {
        return std::max(0.0,(_yBase - _yHeight)) / 80.0;
    }
    else if (Xms>_xOffset && Xms<(_xOffset + _xWidth)) {
        double ti = (Xms - _xOffset);

        double b = 0.0001 * exp(_curve / 7.0);

        double ki = _yHeight * (1.0 - ti / _xWidth) - b * ti*(_xWidth - ti);
        //double m = _yHeight / _xWidth;
        //double inter =
        //double ki = m * (Xms - _xOffset) + _yBase;

        return std::max(std::min(_yBase - ki,_yBase),std::max(0.0,(_yBase - _yHeight))) / 80.0;
    }
    else {
        return _yBase / 80.0;
    }

    // return (sin(x * 30) + 1.0)/2.0;
    /*double voff = (_yHeight == 0.0) ? 0.001 : _yHeight;
    double hoff = (_xOffset == 0.0) ? 0.001 : _xOffset;

    double m = voff / hoff;

    return std::min(1.0, std::min(m * x,voff));*/
    /*if(x>off) {
        return y;
    } else {
        return std::min(x * 10,y);
    }*/
}

std::vector<std::pair<double, double> > TVGTwoPoints::getReferencePoints() const
{
    std::vector<std::pair<double, double> > result;
    result.push_back(std::pair<double, double>(_xOffset/200.0,(_yBase - _yHeight)/80.0));
    result.push_back(std::pair<double, double>((_xOffset+_xWidth)/200.0,_yBase/80.0));
    return result;
}

TVGType TVGTwoPoints::getType() const
{
    return TVGType::TVG2PointType;
}
