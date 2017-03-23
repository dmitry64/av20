#include "rxchannel.h"
#include <string.h>
#include <QDebug>


void RxChannel::setPrismTime(uint8_t prismTime)
{
    _prismTime = prismTime;
}

QString RxChannel::getName() const
{
    return _name;
}

void RxChannel::setName(const QString &name)
{
    _name = name;
}

int RxChannel::getMarkerPos() const
{
    return _markerPos;
}

void RxChannel::setMarkerPos(int markerPos)
{
    _markerPos = markerPos;
}

const TVGCurve *RxChannel::getTvgCurve() const
{
    return _tvgCurve;
}

void RxChannel::setTvgCurve(TVGCurve *tvgCurve)
{
    if(_tvgCurve!=0) {
        delete _tvgCurve;
    }
    _tvgCurve = tvgCurve->clone();
}

uint8_t RxChannel::getPrismTime() const
{
    return _prismTime;
}

RxChannel::RxChannel() : _name("none"),_prismTime(0), _tvgCurve(0), _markerPos(0)
{
}

RxChannel::RxChannel(const RxChannel &original) : _name(original._name), _prismTime(original._prismTime), _tvgCurve(original._tvgCurve->clone()), _markerPos(original._markerPos)
{

}

RxChannel::~RxChannel()
{
    if(_tvgCurve!=0) {
        delete _tvgCurve;
    }
}

QDomElement RxChannel::generateXML(QDomDocument &doc) const
{
    QDomElement rx = doc.createElement("rx");

    QDomElement name = doc.createElement("name");
    name.appendChild(doc.createTextNode(_name));
    rx.appendChild(name);

    QDomElement prismTime = doc.createElement("prismTime");
    prismTime.appendChild(doc.createTextNode(QString::number(_prismTime)));
    rx.appendChild(prismTime);

    QDomElement tvg = _tvgCurve->generateXML(doc);
    rx.appendChild(tvg);

    return rx;
}

void RxChannel::loadXML(const QDomNode &node)
{
    _tvgCurve = generateTVGFromXML(node.firstChildElement("tvg"));
    _prismTime = node.firstChildElement("prismTime").text().toUInt();
    _name = node.firstChildElement("name").text();
}

RxChannel &RxChannel::operator=(const RxChannel &L)
{
    if (this == &L) {
        return *this;
    }
    else {
        _name = L._name;
        _prismTime = L._prismTime;
        TVGCurve * newTvgCurve = L._tvgCurve->clone();
        if(_tvgCurve!=0) {
            delete _tvgCurve;
        }
        _tvgCurve = newTvgCurve;
        _markerPos = L._markerPos;
        return *this;
    }

}

TVGCurve *RxChannel::generateTVGFromXML(const QDomNode &tvg)
{
    TVGCurve * result = 0;
    QDomElement element = tvg.toElement();

    auto attribs = tvg.attributes();
    if(attribs.contains("type")) {

        QDomNode type = attribs.namedItem("type");

        if(type.toAttr().value().compare("single") == 0) {
            double yBase = element.firstChildElement("yBase").text().toDouble();
            double xOffset = element.firstChildElement("xOffset").text().toDouble();
            double yHeight = element.firstChildElement("yHeight").text().toDouble();
            double xWidth = element.firstChildElement("xWidth").text().toDouble();
            double curve = element.firstChildElement("curve").text().toDouble();

            result = new TVGSinglePoint(yBase,xOffset,xWidth,yHeight,curve);
        }
    }

    Q_ASSERT(result);
    return result;
}
