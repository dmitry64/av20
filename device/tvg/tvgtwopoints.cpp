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

void TVGTwoPoints::setYBase(double yBase)
{
    _yBase = yBase;
}

void TVGTwoPoints::setXOffset(double xOffset)
{
    _xOffset = xOffset;
}

void TVGTwoPoints::setYHeight(double yHeight)
{
    _yHeight = yHeight;
}

void TVGTwoPoints::setXWidth(double xWidth)
{
    _xWidth = xWidth;
}

void TVGTwoPoints::setCurve(double curve)
{
    _curve = curve;
}

TVGTwoPoints::TVGTwoPoints() : _yBase(60), _xOffset(50), _yHeight(20), _xWidth(50), _curve(25)
{

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

        return std::max(std::min(_yBase - ki,_yBase),std::max(0.0,(_yBase - _yHeight))) / 80.0;
    }
    else {
        return _yBase / 80.0;
    }

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

void TVGTwoPoints::fillTVGFromXML(const QDomNode &tvg)
{
    QDomElement element = tvg.toElement();
    _yBase = element.firstChildElement("yBase").text().toDouble();
    _xOffset = element.firstChildElement("xOffset").text().toDouble();
    _yHeight = element.firstChildElement("yHeight").text().toDouble();
    _xWidth = element.firstChildElement("xWidth").text().toDouble();
    _curve = element.firstChildElement("curve").text().toDouble();
}
