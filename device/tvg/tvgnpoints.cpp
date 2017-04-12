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

TVGNPoints::TVGNPoints(const TVGNPoints & original) : _points(original._points)
{
    Q_ASSERT(_points.size()>1);
}

TVGCurve *TVGNPoints::clone() const
{
    return new TVGNPoints(*this);
}

double TVGNPoints::getSample(double x) const
{
    Q_ASSERT(_points.size()>1);
    if(x==0.0) {
        return _points.begin().operator*().second;
    }

    auto begin = _points.begin();
    auto end = --(_points.end());
    for(auto it=_points.begin(); it!=_points.end(); it++) {
        if(it.operator*().first>=x) {
            end = it;
            begin = --it;
            break;
        }
    }
    double deltax = (end.operator*().first - begin.operator*().first);
    double m;
    if(deltax!=0.0) {
        m = (end.operator*().second - begin.operator*().second) / deltax;
    }
    else {
        m = 0;
    }
    double val = m * (x - begin.operator*().first) + begin.operator*().second;

    return std::min(std::max(val,0.0),1.0);
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
    Q_ASSERT(_points.size()>1);
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

void TVGNPoints::fillTVGFromXML(const QDomNode &tvg)
{
    _points.clear();
    QDomNode points = tvg.firstChildElement("points");
    auto pointsList = points.childNodes();
    for(int i=0; i<pointsList.size(); i++) {
        QDomNode point = pointsList.at(i);
        QString xStr = point.firstChildElement("x").text();
        QString yStr = point.firstChildElement("y").text();
        std::pair<double,double> pair(xStr.toDouble(),yStr.toDouble());
        _points.push_back(pair);
    }
    Q_ASSERT(_points.size()>1);
}
