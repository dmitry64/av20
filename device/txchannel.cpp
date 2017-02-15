#include "txchannel.h"

PulserFreq TxChannel::freq() const
{
    return _freq;
}

void TxChannel::setFreq(const PulserFreq &freq)
{
    _freq = freq;
}

PulserProg TxChannel::prog() const
{
    return _prog;
}

void TxChannel::setProg(const PulserProg &prog)
{
    _prog = prog;
}

bool TxChannel::doubleMode() const
{
    return _doubleMode;
}

void TxChannel::setDoubleMode(bool doubleMode)
{
    _doubleMode = doubleMode;
}

TxChannel::TxChannel() : _freq(PulserFreq::Freq_1_0_MHz), _prog(PulserProg::Prog_1), _doubleMode(false)
{

}
