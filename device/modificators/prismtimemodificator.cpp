#include "prismtimemodificator.h"

PrismTimeModificator::PrismTimeModificator(ChannelID channel, uint8_t value) : _value(value), _channel(channel)
{

}

void PrismTimeModificator::apply(Core *core)
{
    /*core->getCalibration()->getChannel(_channel)->rx()->setPrismTime(_value);
    core->applyCurrentCalibrationToDevice();*/
}
