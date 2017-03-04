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
    return _tvgCurve->clone();
}

void RxChannel::setTvgCurve(const TVGCurve *tvgCurve)
{
    Q_ASSERT(tvgCurve);
    if(_tvgCurve!=0) {
        delete _tvgCurve;
    }
    _tvgCurve = tvgCurve;
}

uint8_t RxChannel::getPrismTime() const
{
    return _prismTime;
}

RxChannel::RxChannel() : _prismTime(0), _tvgCurve(0), _markerPos(0)
{

}


RxChannel::~RxChannel()
{
    // Q_ASSERT(_tvgCurve);
    //delete _tvgCurve;
}
