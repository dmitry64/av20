#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include "stdint.h"

#include "device/tvg/tvgcurve.h"
#include "device/definitions.h"

class RxChannel
{

    std::string _name;
    uint8_t _prismTime;
    const TVGCurve * _tvgCurve;
    int _markerPos;
    std::vector<Gate> _gates;

public:
    RxChannel();
    RxChannel(RxChannel * original);
    ~RxChannel();

    void setPrismTime(uint8_t prismTime);
    std::vector<Gate> gates() const;
    void setGates(const std::vector<Gate> &gates);

    std::string getName() const;
    void setName(const std::string &name);
    int getMarkerPos() const;
    void setMarkerPos(int markerPos);
    const TVGCurve *getTvgCurve() const;
    void setTvgCurve(const TVGCurve *tvgCurve);
    uint8_t getPrismTime() const;
};

#endif // CHANNEL_H
