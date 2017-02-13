#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include "stdint.h"

#include "definitions.h"

class Channel
{
    uint8_t _index;
    std::string _name;
    int _baseSensLevel;
    std::vector<uint8_t> _tvgPoints;
    TVGMode _tvgMode;
    int _prismTime;
    std::vector<Gate> _gates;


    uint8_t _colorRed;
    uint8_t _colorGreen;
    uint8_t _colorBlue;
public:
    Channel();
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
    std::vector<Gate> gates() const;
    void setGates(const std::vector<Gate> &gates);
    void setIndex(const uint8_t &index);
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    uint8_t getColorRed();
    uint8_t getColorGreen();
    uint8_t getColorBlue();
    std::string getName() const;
    void setName(const std::string &name);
};

#endif // CHANNEL_H
