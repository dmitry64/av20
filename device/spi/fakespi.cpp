#include "fakespi.h"
#include <QDebug>
#include "math.h"

uint8_t getTVGSample(uint8_t * ptr, int sampleNum) {
    int bit = sampleNum * 7;
    uint8_t res = 0x00;
    res |= getBitFromByteArray(ptr,bit);
    res |= getBitFromByteArray(ptr,bit+1) << 1;
    res |= getBitFromByteArray(ptr,bit+2) << 2;
    res |= getBitFromByteArray(ptr,bit+3) << 3;
    res |= getBitFromByteArray(ptr,bit+4) << 4;
    res |= getBitFromByteArray(ptr,bit+5) << 5;
    res |= getBitFromByteArray(ptr,bit+6) << 6;
    return res;
}

uint8_t FakeSPI::getNextTact()
{
    for(int i=_currentTact+1; i<MAX_TACTS_COUNT; i++) {
        if(_state.getTactByIndex(i)._CR & 0b00000001) {
            return i;
        }
    }
    for(int i=0; i<MAX_TACTS_COUNT; i++) {
        if(_state.getTactByIndex(i)._CR & 0b00000001) {
            return i;
        }
    }
    return -1;
}

void FakeSPI::updateCounters()
{
    for(int i=0; i<8; i++) {
        int cur = _counters[i]->load();
        cur++;
        _counters[i]->store(cur);
    }
}

void FakeSPI::setAScanForLine1(uint8_t *dest)
{
    TactRegisters tact = _state.getTactByIndex(_currentTact);
    uint8_t chan = ((tact._TR1 & 0b01110000) >> 4);
    int ascanL1Counter = _counters[chan]->load();
    int ascanL1Counter2 = ascanL1Counter;

    //qDebug() << "Chan: "<<chan << "Tact: " <<tact._TR1;
    TVG tvg = _state.getTvgForChannel(chan);
    //int last = 0;
    dest[0] = ascanL1Counter;
    dest[1] = 12;
    dest[2] = _currentTact;
    dest[3] = chan;
    dest[4] = 0;
    dest[5] = 8;
    dest[6] = 0;
    dest[7] = 0;

    for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        double x = (i + sin(ascanL1Counter2/9.0) * 120.14 + (chan-4.0) * 50.0 - 400.0) / 16.0 ;
        double res = 127.0;
        if(x!=0) {
            res = std::max((((sin(x)/x) + 1)/2.0)*255.0 - 128.0 ,0.0);
        }

        res *= getTVGSample( tvg._samples, i/4) / 127.0;
        res *= (2.3 * (ascanL1Counter2 % 255) + 60.0)/255.0 ;
        int val = round(res);
        unsigned char sh = val;
        dest[i+ASCAN_HEADER_SIZE] = sh;
    }
}

void FakeSPI::setAScanForLine2(uint8_t *dest)
{
    TactRegisters tact = _state.getTactByIndex(_currentTact);
    uint8_t chan = ((tact._TR2 & 0b01110000) >> 4);
    int ascanL2Counter = _counters[chan]->load();
    int ascanL2Counter2 = ascanL2Counter;
    TVG tvg = _state.getTvgForChannel(chan);

    dest[0] = ascanL2Counter;
    dest[1] = 12;
    dest[2] = _currentTact;
    dest[3] = chan;
    dest[4] = 0;
    dest[5] = 8;
    dest[6] = 0;
    dest[7] = 0;
    //int last = 0;
    for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        double x = (i + sin(ascanL2Counter2/9.0) * 120.14 + (chan-4.0) * 50.0 - 400.0) / 8.0 ;
        double res = 127.0;
        if(x!=0) {
            res = std::max((((sin(x)/x) + 1)/2.0)*255.0 - 128.0 ,0.0);
        }

        res *= getTVGSample( tvg._samples, i/4) / 127.0;
        res *= (1.3 * (ascanL2Counter2 % 255) + 60.0)/255.0 ;
        int val = round(res);
        unsigned char sh = val;
        dest[i+ASCAN_HEADER_SIZE] = sh;
    }
}

void FakeSPI::run()
{
    while(true){
        updateCounters();
        usleep(50000);
        if(_specialCounter == 77) {
            //_state.setUSM_SR(_state.USM_SR() ^ 0b00001000);
        }

        if(_specialCounter == 177) {
           // _state.setUSM_SR(_state.USM_SR() ^ 0b10000000);
        }

        _specialCounter++;
    }
}

FakeSPI::FakeSPI() : DeviceInterface()
{
    for (int i=0; i<8; i++) {
        std::atomic_int * a = new std::atomic_int(1);
        _counters.push_back(a);
    }
    _specialCounter = 0;
}

void FakeSPI::init()
{
    _currentTact = -1;
    start();
}

void FakeSPI::getRegister(uint8_t reg, uint32_t length, uint8_t *dest)
{
    switch(reg) {
    case 0x00:
        Q_ASSERT(length==1);
        dest[0] = 0x00;
        break;
    case 0x01:
        Q_ASSERT(length==1);
        dest[0] = 0xFF;
        break;
    case 0x02:
        Q_ASSERT(length==1);
        dest[0] = 0xAE;
        break;
    case 0x03:
        Q_ASSERT(length==1);
        dest[0] = _state.USM_SR();
        break;
    case 0x04:
        Q_ASSERT(length==1);
        dest[0] = _state.USM_CR();
        break;
    case 0x05:
        Q_ASSERT(length==1);
        dest[0] = _state.TRG_CR();
        break;
    case 0x06:
        Q_ASSERT(length==1);
        dest[0] = _state.TRG_DS();
        break;
    case 0x07:
        Q_ASSERT(length==1);
        dest[0] = _state.TRG_TS();
        break;
    case 0x08:
        Q_ASSERT(length==1);
        dest[0] = _state.PWR_CR();
        break;
    case 0x09:
        Q_ASSERT(length==1);
        dest[0] = _state.ODO_CR();
        break;
    case 0x7C:
        if(_currentTact!=255)
            setAScanForLine1(dest);
        break;
    case 0x7D:
        if(_currentTact!=255)
            setAScanForLine2(dest);
        break;
    }

    usleep(10);
}

void FakeSPI::setRegister(uint8_t reg, const uint32_t length, uint8_t *src)
{
    switch(reg) {
    case 0x05:
        _state.setTRG_CR(src[0]);
        if((src[0] & 0b00000001) !=0) {

            _state.setUSM_SR(_state.USM_SR() | 0b00000001);
            _currentTact = getNextTact();

        }
        break;
    case 0x06:
        _state.setTRG_DS(src[0]);
        break;
    case 0x07:
        _state.setTRG_TS(src[0]);
        break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
        TVG tvg;
        for(uint32_t i=0; i<length; i++) {
            tvg._samples[i] = src[i];
        }
        _state.setTVGForChannel(reg - 0x40, tvg);
        break;
    default:
        if(reg >= 0x10 && reg <=0x3f) {
            _state.setChannelsTableRegister(reg,src[0]);
        } else {
            qDebug() << "FakeSPI: unknown register" <<reg;
        }
        break;
    }
    usleep(10);
}

bool FakeSPI::setAndTestRegister(uint8_t reg, const uint32_t length, uint8_t *src)
{
    setRegister(reg,length,src);
    usleep(10);
    return false;
}

bool FakeSPI::getErrorFlag() const
{
    return false;
}
