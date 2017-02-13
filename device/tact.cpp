#include "tact.h"
#include <string.h>
#include <QDebug>


bool Tact::getTx1Enabled() const
{
    return _tx1Enabled;
}

bool Tact::getRx1Enabled() const
{
    return _rx1Enabled;
}

bool Tact::getTx2Enabled() const
{
    return _tx2Enabled;
}

bool Tact::getRx2Enabled() const
{
    return _rx2Enabled;
}

uint8_t Tact::getTx1() const
{
    return _tx1;
}

uint8_t Tact::getRx1() const
{
    return _rx1;
}

uint8_t Tact::getTx2() const
{
    return _tx2;
}

uint8_t Tact::getRx2() const
{
    return _rx2;
}

void Tact::setTx1Enabled(bool tx1Enabled)
{
    _tx1Enabled = tx1Enabled;
}

void Tact::setRx1Enabled(bool rx1Enabled)
{
    _rx1Enabled = rx1Enabled;
}

void Tact::setTx2Enabled(bool tx2Enabled)
{
    _tx2Enabled = tx2Enabled;
}

void Tact::setRx2Enabled(bool rx2Enabled)
{
    _rx2Enabled = rx2Enabled;
}

void Tact::setTx1(const uint8_t &tx1)
{
    _tx1 = tx1;
}

void Tact::setRx1(const uint8_t &rx1)
{
    _rx1 = rx1;
}

void Tact::setTx2(const uint8_t &tx2)
{
    _tx2 = tx2;
}

void Tact::setRx2(const uint8_t &rx2)
{
    _rx2 = rx2;
}

bool Tact::getTactEnabled() const
{
    return _tactEnabled;
}

void Tact::setTactEnabled(bool tactEnabled)
{
    _tactEnabled = tactEnabled;
}

PulserProg Tact::getProg1() const
{
    return _prog1;
}

PulserFreq Tact::getFreq1() const
{
    return _freq1;
}

PulserProg Tact::getProg2() const
{
    return _prog2;
}

PulserFreq Tact::getFreq2() const
{
    return _freq2;
}

Tact::Tact() :
    _tactEnabled(false),
    _diffMode(false),
    _tx1Enabled(false),
    _tx1(0x00),
    _rx1Enabled(false),
    _rx1(0x00),
    _double1(false),
    _prog1(PulserProg::Prog_1),
    _freq1(PulserFreq::Freq_1_0_MHz),
    _tx2Enabled(false),
    _tx2(0x00),
    _rx2Enabled(false),
    _rx2(0x00),
    _double2(false),
    _prog2(PulserProg::Prog_1),
    _freq2(PulserFreq::Freq_1_0_MHz)
{

}

TactRegisters Tact::getRegisters()
{
    TactRegisters reg;
    reg._CR = 0x00;
    reg._CR |= ((_diffMode & 0b00000001) << 1);
    reg._CR |= (_tactEnabled & 0b00000001);

    reg._TR1 = 0x00;
    reg._TR1 |= ((_rx1Enabled & 0b00000001) << 7);
    reg._TR1 |= ((_rx1 & 0b00000111) << 4);
    reg._TR1 |= ((_tx1Enabled & 0b00000001) << 3);
    reg._TR1 |= (_tx1 & 0b00000111);

    reg._PULSER1 = 0x00;
    reg._PULSER1 |= ((_double1 & 0b00000001) << 7);
    uint8_t prog1 = _prog1;
    reg._PULSER1 |= ((prog1 & 0b00001111) << 3);
    uint8_t freq1 = _freq1;
    reg._PULSER1 |= (freq1 & 0b00001111);

    reg._TR2 = 0x00;
    reg._TR2 |= ((_rx2Enabled & 0b00000001) << 7);
    reg._TR2 |= ((_rx2 & 0b00000111) << 4);
    reg._TR2 |= ((_tx2Enabled & 0b00000001) << 3);
    reg._TR2 |= (_tx2 & 0b00000111);

    reg._PULSER2 = 0x00;
    reg._PULSER2 |= ((_double2 & 0b00000001) << 7);
    uint8_t prog2 = _prog2;
    reg._PULSER1 |= ((prog2 & 0b00001111) << 3);
    uint8_t freq2 = _freq2;
    reg._PULSER2 |= (freq2 & 0b00001111);

    reg._RESERVED = 0x00;

    return reg;
}
