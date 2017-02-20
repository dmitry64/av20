#include "rxchannel.h"
#include <string.h>
#include <QDebug>


void RxChannel::setPrismTime(uint8_t prismTime)
{
    _prismTime = prismTime;
}

std::vector<Gate> RxChannel::gates() const
{
    return _gates;
}

void RxChannel::setGates(const std::vector<Gate> &gates)
{
    _gates = gates;
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

TVGCurve *RxChannel::getTvgCurve() const
{
    return _tvgCurve;
}

void RxChannel::setTvgCurve(TVGCurve *tvgCurve)
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

RxChannel::RxChannel() : _prismTime(0), _markerPos(0), _tvgCurve(0)
{

}

RxChannel::RxChannel(RxChannel *original)
{
    Q_ASSERT(original);
    _name = original->getName();
    Q_ASSERT(original->getTvgCurve());
    _tvgCurve = original->getTvgCurve()->clone();
    _prismTime = original->getPrismTime();
    _markerPos = original->getMarkerPos();
    /*for(size_t i=0; i<original->gates().size(); i++) {
        _gates.push_back(original->gates().at(i));
    }*/
    _gates = original->gates();
}

RxChannel::~RxChannel()
{
    Q_ASSERT(_tvgCurve);
    delete _tvgCurve;
}

