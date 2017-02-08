#include "tvgsimplemodificator.h"

TVGSimpleModificator::TVGSimpleModificator(int channel, TVG & value) : Modificator(), _value(value), _channel(channel)
{
}

void TVGSimpleModificator::apply(Device *device)
{
    device->setTVG(_channel, _value);
}
