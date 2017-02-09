#include "tvgsimplemodificator.h"
#include "core.h"

TVGSimpleModificator::TVGSimpleModificator(int channel, int value) : Modificator(), _value(value), _channel(channel)
{
}

void setBit(uint8_t * ptr, int bit, uint8_t val) {
    uint8_t prev = ptr[bit/8];
    ptr[bit/8] |= (((prev >> (bit % 8)) | val) << (bit % 8));
}

void TVGSimpleModificator::apply(Device *device)
{
    std::vector<uint8_t> samples;
    for(int i=0; i<TVG_SAMPLES_SIZE; i++) {
        uint8_t sample = std::min(127, i + _value);
        samples.push_back(sample);
    }

    uint8_t packedValues[TVG_SAMPLES_BYTES];
    memset(packedValues,0,TVG_SAMPLES_BYTES);
    for(int i=0; i<samples.size(); i++) {
        for(int j=0; j<7; j++) {
            setBit(packedValues,i*7 + j, (samples[i] >> j) & 0b00000001);
        }
    }


    for(int i=0; i<TVG_SAMPLES_BYTES; i++) {
        _tvg._samples[i] = packedValues[i];
    }
    device->setTVG(_channel, _tvg);
}

void TVGSimpleModificator::notify(Core *core)
{
    core->getCalibration()->setTvgCurve(_value);
    core->notifyTVG(_tvg);
}
