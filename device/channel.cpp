#include "channel.h"
#include <string.h>

Channel::Channel(uint8_t index) :_index(index), _baseSensLevel(0), _tvgMode(TVGMode::CurveMode)
{

}

int Channel::baseSensLevel() const
{
    return _baseSensLevel;
}

void Channel::setBaseSensLevel(int baseSensLevel)
{
    _baseSensLevel = baseSensLevel;
}

std::vector<uint8_t> Channel::tvgPoints() const
{
    return _tvgPoints;
}

void Channel::setTvgPoints(const std::vector<uint8_t> &tvgPoints)
{
    _tvgPoints = tvgPoints;
}

TVGMode Channel::tvgMode() const
{
    return _tvgMode;
}

void Channel::setTvgMode(const TVGMode &tvgMode)
{
    _tvgMode = tvgMode;
}

void setBit(uint8_t * ptr, int bit, uint8_t val) {
    uint8_t prev = ptr[bit/8];
    ptr[bit/8] |= (((prev >> (bit % 8)) | val) << (bit % 8));
}

TVG Channel::generateTVG()
{
    std::vector<uint8_t> samples;
    for(int i=0; i<TVG_SAMPLES_SIZE; i++) {
        uint8_t sample = std::min(127, i + _baseSensLevel);
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
