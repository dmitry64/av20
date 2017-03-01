#include "tvgmodificator.h"

TVGModificator::TVGModificator(ChannelID channel, const TVGCurve *curve) : _channel(channel), _curve(curve)
{

}

void TVGModificator::apply(Core *core)
{
    core->getCalibration()->getChannel(_channel)->rx()->setTvgCurve(_curve);
    core->applyCurrentCalibrationToDevice();
    core->notifyChannel((core->getCalibration()->getChannel(_channel)));
}
