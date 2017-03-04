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
    qDebug() << "Set";
    _tvgCurve = tvgCurve;
}

uint8_t RxChannel::getPrismTime() const
{
    return _prismTime;
}

RxChannel::RxChannel() : _prismTime(0), _tvgCurve(0), _markerPos(0)
{
    qDebug() << "Created";

}

RxChannel::RxChannel(const RxChannel &original)
{
    _name = original._name;
    _prismTime = original._prismTime;
    TVGCurve * tvgCurve = original._tvgCurve->clone();
    _tvgCurve = tvgCurve;

    _markerPos = original._markerPos;
}

RxChannel::~RxChannel()
{
    qDebug() << "Deleted";
    if(_tvgCurve!=0) {
        //delete _tvgCurve;
    }
}
