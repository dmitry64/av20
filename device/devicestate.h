#ifndef DEVICESTATE_H
#define DEVICESTATE_H

#include "definitions.h"
//#include "device.h"

class DeviceState
{
    //Device * _device;


    // Config registers
    uint8_t _USM_ID;
    uint8_t _USM_SR;
    uint8_t _USM_CR;
    uint8_t _TRG_CR;
    uint8_t _TRG_DS;
    uint8_t _TRG_TS;
    uint8_t _PWR_CR;
    uint8_t _ODO_CR;

    uint8_t _RESERVED_0A;
    uint8_t _RESERVED_0B;
    uint8_t _RESERVED_0C;
    uint8_t _RESERVED_0D;
    uint8_t _RESERVED_0E;
    uint8_t _RESERVED_0F;

    // Channels table
    TactRegisters _tactTable[8];

    // TVG
    TVG _tvg[8];

    // A-scan
    /*AScanHeader _headerA;
    uint8_t * _ascanSamplesA;//[800];
    AScanHeader _headerB;
    uint8_t * _ascanSamplesB;//[800];*/

public:
    DeviceState();
    void applyState();

    //uint8_t * getAscanForChannel(uint8_t activeChannel);

    void setTVGForChannel(uint8_t index, TVG tvg);
    TVG getTvgForChannel(uint8_t index);
    void setChannelsTableTact(uint8_t index, TactRegisters tact);
    void setChannelsTableRegister(uint8_t reg, uint8_t value);
    TactRegisters getTactByIndex(uint8_t index);

    uint8_t USM_ID() const;
    void setUSM_ID(const uint8_t &USM_ID);
    uint8_t USM_SR() const;
    void setUSM_SR(const uint8_t &USM_SR);
    uint8_t USM_CR() const;
    void setUSM_CR(const uint8_t &USM_CR);
    uint8_t TRG_CR() const;
    void setTRG_CR(const uint8_t &TRG_CR);
    uint8_t TRG_DS() const;
    void setTRG_DS(const uint8_t &TRG_DS);
    uint8_t TRG_TS() const;
    void setTRG_TS(const uint8_t &TRG_TS);
    uint8_t PWR_CR() const;
    void setPWR_CR(const uint8_t &PWR_CR);
    uint8_t ODO_CR() const;
    void setODO_CR(const uint8_t &ODO_CR);


};

#endif // DEVICESTATE_H
