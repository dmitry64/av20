#include "pulserfreqmodificator.h"

PulserFreqModificator::PulserFreqModificator(const ChannelsInfo & info, PulserFreq value) : _info(info),_freq(value)
{

}

void PulserFreqModificator::apply(Core *core)
{
    auto calibration = core->getCalibration();
    auto channel = calibration.getChannel(_info._channel);
    auto displayChannels = channel.getDisplayChannels();
    auto disp = displayChannels[_info._displayChannel];
    auto tx = disp.getTx();
    tx.setFreq(_freq);
    disp.setTx(tx);
    displayChannels[_info._displayChannel] = disp;
    channel.setDisplayChannels(displayChannels);

    core->applyChannelsModification(_info._channel,channel);
    core->applyCurrentCalibrationToDevice();
    core->notifyChannel(channel);
}
