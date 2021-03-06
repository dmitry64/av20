#include "devicestate.h"

#include <QDebug>

uint8_t DeviceState::USM_ID() const
{
    return _USM_ID;
}

uint8_t DeviceState::USM_SR() const
{
    return _USM_SR;
}

uint8_t DeviceState::USM_CR() const
{
    return _USM_CR;
}

void DeviceState::setUSM_CR(const uint8_t &USM_CR)
{
    _USM_CR = USM_CR;
}

uint8_t DeviceState::TRG_CR() const
{
    return _TRG_CR;
}

void DeviceState::setTRG_CR(const uint8_t &TRG_CR)
{
    _TRG_CR = TRG_CR;
}

uint8_t DeviceState::TRG_DS() const
{
    return _TRG_DS;
}

void DeviceState::setTRG_DS(const uint8_t &TRG_DS)
{
    _TRG_DS = TRG_DS;
}

uint8_t DeviceState::TRG_TS() const
{
    return _TRG_TS;
}

void DeviceState::setTRG_TS(const uint8_t &TRG_TS)
{
    _TRG_TS = TRG_TS;
}

uint8_t DeviceState::PWR_CR() const
{
    return _PWR_CR;
}

void DeviceState::setPWR_CR(const uint8_t &PWR_CR)
{
    _PWR_CR = PWR_CR;
}

uint8_t DeviceState::ODO_CR() const
{
    return _ODO_CR;
}

void DeviceState::setODO_CR(const uint8_t &ODO_CR)
{
    _ODO_CR = ODO_CR;
}

void DeviceState::setUSM_ID(const uint8_t &USM_ID)
{
    _USM_ID = USM_ID;
}

void DeviceState::setUSM_SR(const uint8_t &USM_SR)
{
    _USM_SR = USM_SR;
}

DeviceState::DeviceState():
    _USM_ID(0),
    _USM_CR(0),
    _USM_SR(0),
    _TRG_CR(0),
    _TRG_DS(0),
    _TRG_TS(0),
    _PWR_CR(0),
    _ODO_CR(0)/*,
    _RESERVED_0A(0),
    _RESERVED_0B(0),
    _RESERVED_0C(0),
    _RESERVED_0D(0),
    _RESERVED_0E(0),
    _RESERVED_0F(0)*/
{
}

void DeviceState::setTVGForChannel(uint8_t index,const TVG & tvg)
{
    for(int y=0; y<TVG_SAMPLES_BYTES; y++) {
        _tvg[index]._samples[y] = tvg._samples[y];
    }
}

TVG DeviceState::getTvgForChannel(uint8_t index) const
{
    return _tvg[index];
}

void DeviceState::setChannelsTableTact(uint8_t index,const TactRegisters & tact)
{
    _tactTable[index]._CR = tact._CR;
    _tactTable[index]._PULSER1 = tact._PULSER1;
    _tactTable[index]._PULSER2 = tact._PULSER2;
    _tactTable[index]._TR1 = tact._TR1;
    _tactTable[index]._TR2 = tact._TR2;
    _tactTable[index]._RESERVED = tact._RESERVED;
}

void DeviceState::setChannelsTableRegister(uint8_t reg, uint8_t value)
{

    switch((reg-0x10) % 6) {
    case 0x00:
        _tactTable[(reg-0x10) / 6]._CR = value;
        break;
    case 0x01:
        _tactTable[(reg-0x10) / 6]._TR1 = value;
        break;
    case 0x02:
        _tactTable[(reg-0x10) / 6]._PULSER1 = value;
        break;
    case 0x03:
        _tactTable[(reg-0x10) / 6]._TR2 = value;
        break;
    case 0x04:
        _tactTable[(reg-0x10) / 6]._PULSER2 = value;
        break;
    case 0x05:
        _tactTable[(reg-0x10) / 6]._RESERVED = value;
        break;
    }
}

TactRegisters DeviceState::getTactByIndex(uint8_t index) const
{
    Q_ASSERT(index < 8);
    return _tactTable[index];
}
