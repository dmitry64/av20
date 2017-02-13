#include "tvgsimplemodificator.h"
#include "core.h"
#include <QDebug>

TVGSimpleModificator::TVGSimpleModificator(int channel, int value) : Modificator(), _value(value), _channel(channel)
{
}



void TVGSimpleModificator::apply(Core *core)
{
    core->getCalibration()->getChannel(_channel)->setBaseSensLevel(_value);
    TVG tvg = core->getCalibration()->getChannel(_channel)->generateTVG();
    core->getDevice()->setTVG(_channel, tvg);
    core->notifyChannel(*(core->getCalibration()->getChannel(_channel)));
}

