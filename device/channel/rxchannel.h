#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include "stdint.h"

#include "device/tvg/tvgcurve.h"
#include "device/definitions.h"

#include <QtXml/QDomElement>

class RxChannel
{
    std::string _name;
    uint8_t _prismTime;
    TVGCurve * _tvgCurve;
    int _markerPos;

public:
    RxChannel();
    RxChannel(const RxChannel & original);
    ~RxChannel();
    QDomElement generateXML(QDomDocument & doc) const;
    RxChannel & operator=(const RxChannel &L);
    void setPrismTime(uint8_t prismTime);
    std::vector<Gate> gates() const;
    void setGates(const std::vector<Gate> &gates);

    std::string getName() const;
    void setName(const std::string &name);
    int getMarkerPos() const;
    void setMarkerPos(int markerPos);
    const TVGCurve *getTvgCurve() const;
    void setTvgCurve(TVGCurve *tvgCurve);
    uint8_t getPrismTime() const;
};

#endif // CHANNEL_H
