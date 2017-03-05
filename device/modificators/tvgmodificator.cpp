#include "tvgmodificator.h"

TVGModificator::TVGModificator(ChannelsInfo info, TVGCurve *curve) : _info(info), _curve(curve)
{

}

TVGModificator::~TVGModificator()
{
    delete _curve;
}

void TVGModificator::apply(Core *core)
{
    auto calibration = core->getCalibration();
    auto channel = calibration.getChannel(_info._channel);
    auto displayChannels = channel.getDisplayChannels();
    auto disp = displayChannels[_info._displayChannel];
    auto rx = disp.getRx();
    rx.setTvgCurve(_curve);
    disp.setRx(rx);
    displayChannels[_info._displayChannel] = disp;
    channel.setDisplayChannels(displayChannels);

    core->applyChannelsModification(_info._channel,channel);
    core->applyCurrentCalibrationToDevice();
    core->notifyChannel(channel);
}
