#include "devicestate.h"



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

DeviceState::DeviceState()
{
    //TriggerMode _triggerMode;
    //_triggerMode = TriggerMode::ProgTRG;
    _USM_ID = 0;
    _USM_CR = 0;
    _USM_SR = 0;
    _TRG_CR = 0;
    _TRG_DS = 0;
    _TRG_TS = 0;
    _PWR_CR = 0;
    _ODO_CR = 0;
}

void DeviceState::applyState()
{

}
/*
uint8_t * DeviceState::getAscanForChannel(uint8_t activeChannel)
{
    switch(activeChannel) {
    case 0:
        return _ascanSamplesA;
    case 1:
        return _ascanSamplesB;
    }
    return _ascanSamplesA;
}
*/
void DeviceState::setTVGForChannel(uint8_t index, TVG tvg)
{
    for(int y=0; y<150; y++) {
        _tvg[index]._samples[y] = tvg._samples[y];
    }
}

void DeviceState::setChannelsTableTact(uint8_t index, Tact tact)
{
    _tactTable[index]._CR = tact._CR;
    _tactTable[index]._PULSER1 = tact._PULSER1;
    _tactTable[index]._PULSER2 = tact._PULSER2;
    _tactTable[index]._TR1 = tact._TR1;
    _tactTable[index]._TR2 = tact._TR2;
    _tactTable[index]._RESERVED = tact._RESERVED;
}
