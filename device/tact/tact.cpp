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

bool Tact::getDiffMode() const
{
    return _diffMode;
}

Tact::Tact() :
    _tactEnabled(false),
    _diffMode(false),
    _tx1Enabled(false),
    _tx1(0x00),
    _rx1Enabled(false),
    _rx1(0x00),
    _tx2Enabled(false),
    _tx2(0x00),
    _rx2Enabled(false),
    _rx2(0x00)
{

}
