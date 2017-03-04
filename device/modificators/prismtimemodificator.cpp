#include "prismtimemodificator.h"

PrismTimeModificator::PrismTimeModificator(ChannelsInfo info, uint8_t value) : _value(value), _info(info)
{

}

void PrismTimeModificator::apply(Core *core)
{
    auto calibration = core->getCalibration();
    auto channel = calibration.getChannel(_info._channel);
    auto displayChannels = channel.getDisplayChannels();
    auto disp = displayChannels[_info._displayChannel];
    auto rx = disp.getRx();
    rx.setPrismTime(_value);
    disp.setRx(rx);
    displayChannels[_info._displayChannel] = disp;
    channel.setDisplayChannels(displayChannels);

    core->applyChannelsModification(_info._channel,channel);
    core->applyCurrentCalibrationToDevice();
    core->notifyChannel(channel);
}
