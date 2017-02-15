#include "rxchannel.h"
#include <string.h>
#include <QDebug>

int RxChannel::prismTime() const
{
    return _prismTime;
}

void RxChannel::setPrismTime(int prismTime)
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

RxChannel::RxChannel() :_baseSensLevel(0), _tvgMode(TVGMode::CurveMode), _prismTime(0)
{

}

int RxChannel::baseSensLevel() const
{
    return _baseSensLevel;
}

void RxChannel::setBaseSensLevel(int baseSensLevel)
{
    _baseSensLevel = baseSensLevel;
}

std::vector<uint8_t> RxChannel::tvgPoints() const
{
    return _tvgPoints;
}

void RxChannel::setTvgPoints(const std::vector<uint8_t> &tvgPoints)
{
    _tvgPoints = tvgPoints;
}

TVGMode RxChannel::tvgMode() const
{
    return _tvgMode;
}

void RxChannel::setTvgMode(const TVGMode &tvgMode)
{
    _tvgMode = tvgMode;
}

void setBit(uint8_t * ptr, int bit, uint8_t val) {
    uint8_t prev = ptr[bit/8];
    ptr[bit/8] |= (((prev >> (bit % 8)) | val) << (bit % 8));
}

TVG RxChannel::generateTVG()
{
    std::vector<uint8_t> samples;
    qDebug() << "Base level:" << _baseSensLevel;
    for(int i=0; i<TVG_SAMPLES_SIZE; i++) {
        uint8_t sample = std::min(127, std::min(64 , i*3) + _baseSensLevel);
        samples.push_back(sample);
    }

    uint8_t packedValues[TVG_SAMPLES_BYTES];
    memset(packedValues,0,TVG_SAMPLES_BYTES);
    for(int i=0; i<samples.size(); i++) {
        for(int j=0; j<7; j++) {
            setBit(packedValues,i*7 + j, (samples[i] >> j) & 0b00000001);
        }
    }

    TVG tvg;

    for(int i=0; i<TVG_SAMPLES_BYTES; i++) {
        tvg._samples[i] = packedValues[i];
    }

    return tvg;
}
