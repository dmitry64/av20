#include "tvgnpoints.h"

void TVGNPoints::setPoints(const std::vector<std::pair<double, double> > &points)
{
    _points = points;
}

TVGNPoints::TVGNPoints()
{
    for(int i=0; i<2; i++) {
        std::pair<double,double> point(i,0.6);
        _points.push_back(point);
    }
}

TVGNPoints::TVGNPoints(const TVGNPoints & original)
{
    _points = original._points;
}

TVGCurve *TVGNPoints::clone() const
{
    return new TVGNPoints(*this);
}

double TVGNPoints::getSample(double x) const
{
    auto begin = _points.begin();
    auto end = _points.end();
    for(auto it=_points.begin(); it!=_points.end(); it++) {
        if(it.operator*().first>=x) {
            end = it;
            begin = --it;
            break;
        }
    }
    double m = (end.operator*().second - begin.operator*().second) / (end.operator*().first - begin.operator*().first);
    double val = m * (x - begin.operator*().first) + begin.operator*().second;

    return val;
}

std::vector<std::pair<double, double> > TVGNPoints::getReferencePoints() const
{
    return _points;
}

TVGType TVGNPoints::getType() const
{
    return TVGType::TVGNPointType;
}

QDomElement TVGNPoints::generateXML(QDomDocument &doc)
{
    QDomElement tvg = doc.createElement("tvg");

    tvg.setAttribute("type","npoint");

    QDomElement points = doc.createElement("points");
    for(auto it=_points.begin(); it!=_points.end(); it++) {
        const std::pair<double,double> & pair = it.operator*();
        QDomElement point = doc.createElement("point");
        QDomElement x = doc.createElement("x");
        x.appendChild(doc.createTextNode(QString::number(pair.first)));
        QDomElement y = doc.createElement("y");
        y.appendChild(doc.createTextNode(QString::number(pair.second)));
        point.appendChild(x);
        point.appendChild(y);
        points.appendChild(point);
    }
    tvg.appendChild(points);

    return tvg;
}
