#include "rxchannel.h"
#include <string.h>
#include <QDebug>


void RxChannel::setPrismTime(uint8_t prismTime)
{
    _prismTime = prismTime;
}

std::string RxChannel::getName() const
{
    return _name;
}

void RxChannel::setName(const std::string &name)
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

RxChannel::RxChannel() : _prismTime(0), _tvgCurve(0), _markerPos(0)
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

    return rx;
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
