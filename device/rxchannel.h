#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include "stdint.h"

#include "definitions.h"

class RxChannel
{

    std::string _name;
    int _baseSensLevel;
    std::vector<uint8_t> _tvgPoints;
    TVGMode _tvgMode;
    int _prismTime;
    std::vector<Gate> _gates;



public:
    RxChannel();
    int baseSensLevel() const;
    void setBaseSensLevel(int baseSensLevel);
    std::vector<uint8_t> tvgPoints() const;
    void setTvgPoints(const std::vector<uint8_t> &tvgPoints);
    TVGMode tvgMode() const;
    void setTvgMode(const TVGMode &tvgMode);
    TVG generateTVG();
    int prismTime() const;
    void setPrismTime(int prismTime);
    std::vector<Gate> gates() const;
    void setGates(const std::vector<Gate> &gates);

    std::string getName() const;
    void setName(const std::string &name);
};

#endif // CHANNEL_H
