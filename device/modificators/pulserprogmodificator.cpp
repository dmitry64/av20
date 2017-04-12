#include "pulserprogmodificator.h"

PulserProgModificator::PulserProgModificator(const ChannelsInfo &info, PulserProg value) : _info(info), _prog(value)
{

}

void PulserProgModificator::apply(Core *core)
{
    auto calibration = core->getCalibration();
    auto channel = calibration.getChannel(_info._channel);
    auto displayChannels = channel.getDisplayChannels();
    auto disp = displayChannels[_info._displayChannel];
    auto tx = disp.getTx();
    tx.setProg(_prog);
    disp.setTx(tx);
    displayChannels[_info._displayChannel] = disp;
    channel.setDisplayChannels(displayChannels);

    core->applyChannelsModification(_info._channel,channel);
    core->applyCurrentCalibrationToDevice();
    core->notifyChannel(channel);
}
