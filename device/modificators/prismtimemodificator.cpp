#include "prismtimemodificator.h"

PrismTimeModificator::PrismTimeModificator(uint8_t channel, uint8_t value) : _value(value), _channel(channel)
{

}

void PrismTimeModificator::apply(Core *core)
{
    core->getCalibration()->getChannel(_channel)->rx()->setPrismTime(_value);
    core->applyCurrentCalibrationToDevice();
}
