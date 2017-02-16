#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include "stdint.h"

#include "device/tvgcurve.h"
#include "definitions.h"



class RxChannel
{

    std::string _name;
    TVGCurve * _tvgCurve;

    int _prismTime;
    int _markerPos;
    std::vector<Gate> _gates;

public:
    RxChannel();
   // int baseSensLevel() const;
    //void setBaseSensLevel(int baseSensLevel);

    int prismTime() const;
    void setPrismTime(int prismTime);
    std::vector<Gate> gates() const;
    void setGates(const std::vector<Gate> &gates);

    std::string getName() const;
    void setName(const std::string &name);
    int getMarkerPos() const;
    void setMarkerPos(int markerPos);
    TVGCurve *getTvgCurve() const;
    void setTvgCurve(TVGCurve *tvgCurve);
};

#endif // CHANNEL_H
