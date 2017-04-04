#include "fakespi.h"
#include <QDebug>
#include "math.h"


uint8_t getTVGSample(uint8_t * ptr, int sampleNum)
{
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
    double time = _timer.elapsed();
    _timer.restart();
    for(uint8_t i=0; i<8; i++) {
        int cur = _counters[i]->load();
        cur+= time;
        _counters[i]->store(cur);
    }

}

unsigned char FakeSPI::sincFunc(TVG tvg, uint8_t chan, int i, int time)
{
    double x = (i + sin(time/999.0) * 120.14 + (chan-4.0) * 50.0 - 400.0) / 16.0 ;
    double res = 127.0;
    if(x!=0) {
        res = std::max((((sin(x)/x) + 1)/2.0)*255.0 - 128.0 ,0.0);
    }

    res *= getTVGSample( tvg._samples, i/4) / 127.0;
    //res *= (2.3 * (time % 255) + 60.0)/255.0 ;
    int val = round(res);
    unsigned char sh = val;

    return sh;
}

unsigned char FakeSPI::sinusFunc(TVG tvg, uint8_t chan, int i, int time)
{
    double x = (i + sin(time/999.0) * 120.14 + (chan-4.0) * 50.0 - 400.0) / 16.0 ;
    double res = 127.0;
    if(x!=0) {
        double val = (((sin(x +time/700.0)) + 1)/2.0)*255.0;
        if(val > 0) {
            res = val;
        }
        else {
            res = - val;
        }
        //res = std::max(val,0.0);
    }

    res *= getTVGSample( tvg._samples, i/4) / 127.0;
    //res *= (2.3 * (time % 255) + 60.0)/255.0 ;
    int val = round(res);
    unsigned char sh = val;

    return sh;
}

unsigned char FakeSPI::cosinusFunc(TVG tvg, uint8_t chan, int i, int time)
{
    double x = (i + (cos(time/999.0) + sin(time/599.0)) * 120.14 + (chan-4.0) * 50.0 - 400.0) / 20.0 ;
    double res = 127.0;
    if(x!=0) {
        res = std::max((((cos(x)) + 1)/2.0)*255.0 - 128.0*(sin(time/1000.0)+1)/2.0 ,0.0);
    }

    res *= getTVGSample( tvg._samples, i/4) / 127.0;
    res *= 2.3;
    int val = round(res);
    unsigned char sh = val;

    return sh;
}

void FakeSPI::generateAscan(uint8_t *dest, bool line)
{
    TactRegisters tact = _state.getTactByIndex(_currentTact);
    uint8_t chan = ((tact._TR1 & 0b01110000) >> 4);
    int ascanL1Counter = _counters[chan]->load();

    TVG tvg = _state.getTvgForChannel(chan);
    dest[0] = ascanL1Counter;
    dest[1] = 12;
    dest[2] = _currentTact;
    dest[3] = chan;
    dest[4] = 0;
    dest[5] = 8;
    dest[6] = 0;
    dest[7] = 0;

    for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        unsigned char sh = 0;
        switch (chan) {
        case 0:
            sh = cosinusFunc(tvg, chan, i, ascanL1Counter);
            break;
        case 1:
            sh = sinusFunc(tvg, chan, i, ascanL1Counter);
            break;
        default:
            sh = sincFunc(tvg, chan, i, ascanL1Counter);
            break;
        }

        dest[i+ASCAN_HEADER_SIZE] = sh;
    }
}

void FakeSPI::setAScanForLine1(uint8_t *dest)
{
    generateAscan(dest, true);
}

void FakeSPI::setAScanForLine2(uint8_t *dest)
{
    generateAscan(dest, false);
}

void FakeSPI::run()
{
    _timer.restart();
    while(_active.load()) {
        updateCounters();
        usleep(50000);
        if(_specialCounter == 77) {
            _state.setUSM_SR(_state.USM_SR() ^ 0b00001000);
        }

        if(_specialCounter == 177) {
            _state.setUSM_SR(_state.USM_SR() ^ 0b10000000);
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
    _currentTact = 0;
}

FakeSPI::~FakeSPI()
{

}

void FakeSPI::init()
{
    _currentTact = -1;
    _active.store(true);
    start();
}

void FakeSPI::finish()
{
    _active.store(false);
    wait();
}

void FakeSPI::getRegister(uint8_t reg, const uint32_t length, uint8_t *dest)
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
        if(_currentTact!=255) {
            setAScanForLine1(dest);
        }
        break;
    case 0x7D:
        if(_currentTact!=255) {
            setAScanForLine2(dest);
        }
        break;
    }

    usleep(10);
}

void FakeSPI::setRegister(uint8_t reg, const uint32_t length, const uint8_t *src)
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
        }
        else {
            qDebug() << "FakeSPI: unknown register" <<reg;
        }
        break;
    }
    usleep(10);
}

bool FakeSPI::setAndTestRegister(uint8_t reg, const uint32_t length, const uint8_t *src)
{
    setRegister(reg,length,src);
    usleep(10);
    return false;
}

bool FakeSPI::getErrorFlag() const
{
    return false;
}
