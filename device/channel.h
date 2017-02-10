#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include "stdint.h"

#include "definitions.h"

class Channel
{
    uint8_t _index;
    int _baseSensLevel;
    std::vector<uint8_t> _tvgPoints;
    TVGMode _tvgMode;
    int _prismTime;

public:
    Channel(uint8_t index);
    int baseSensLevel() const;
    void setBaseSensLevel(int baseSensLevel);
    std::vector<uint8_t> tvgPoints() const;
    void setTvgPoints(const std::vector<uint8_t> &tvgPoints);
    TVGMode tvgMode() const;
    void setTvgMode(const TVGMode &tvgMode);
    TVG generateTVG();
    uint8_t index() const;
    int prismTime() const;
    void setPrismTime(int prismTime);
};

#endif // CHANNEL_H
