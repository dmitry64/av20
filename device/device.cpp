#include "device.h"
#include <QDebug>
#define FAKESPI

TactRegisters Device::getRegistersByTact(uint8_t index, DeviceMode * mode)
{
    TactRegisters reg;
    Tact * tact = mode->getTactByIndex(index);
    tact->getRx1();

    reg._CR = 0x00;
    reg._CR |= ((tact->getDiffMode() & 0b00000001) << 1);
    reg._CR |= (tact->getTactEnabled() & 0b00000001);

    reg._TR1 = 0x00;
    reg._TR1 |= ((tact->getRx1Enabled() & 0b00000001) << 7);
    reg._TR1 |= ((tact->getRx1() & 0b00000111) << 4);
    reg._TR1 |= ((tact->getTx1Enabled() & 0b00000001) << 3);
    reg._TR1 |= (tact->getTx1() & 0b00000111);

    TxChannel * firstTx = mode->getChannel(tact->getTx1())->tx();
    reg._PULSER1 = 0x00;
    reg._PULSER1 |= ((firstTx->doubleMode() & 0b00000001) << 7);
    uint8_t prog1 = firstTx->prog();
    reg._PULSER1 |= ((prog1 & 0b00001111) << 3);
    uint8_t freq1 = firstTx->prog();
    reg._PULSER1 |= (freq1 & 0b00001111);

    reg._TR2 = 0x00;
    reg._TR2 |= ((tact->getRx2Enabled() & 0b00000001) << 7);
    reg._TR2 |= ((tact->getRx2() & 0b00000111) << 4);
    reg._TR2 |= ((tact->getTx2Enabled() & 0b00000001) << 3);
    reg._TR2 |= (tact->getTx2() & 0b00000111);

    TxChannel * secondTx = mode->getChannel(tact->getTx2())->tx();
    reg._PULSER2 = 0x00;
    reg._PULSER2 |= ((secondTx->doubleMode() & 0b00000001) << 7);
    uint8_t prog2 = secondTx->prog();
    reg._PULSER1 |= ((prog2 & 0b00001111) << 3);
    uint8_t freq2 = secondTx->freq();
    reg._PULSER2 |= (freq2 & 0b00001111);

    reg._RESERVED = 0x00;

    return reg;
}

Device::Device(DeviceState *state) :  _state(state)
{
#ifdef FAKESPI
    _spi = new FakeSPI();
#else
    _spi = new DriverSPI("/dev/spidev0.0");
#endif
}

void Device::init()
{
    _spi->init();
    bool status = checkConnection();

    if(status) {
        uint8_t version = getVersion();
        _state->setUSM_ID(version);
        qDebug() << "Device version:" << QString::number(static_cast<unsigned int>(version),16).toUpper();
        fillRegisters();
    } else {
        qFatal("Cannot initialize device!");
    }
}

void Device::fillRegisters()
{
    resetConfigRegisters();
    resetChannelsTable();
    resetTVG();
}

void Device::resetConfigRegisters()
{
    uint8_t trg_cr_send = 0b00000001;
    if(_spi->setAndTestRegister(0x05, 1, &trg_cr_send)) {
        qFatal("TRG_CR Initialization failed!");
    } else {
        qDebug() << "TRG_CR initialized!";
        _state->setTRG_CR(trg_cr_send);
    }

    uint8_t trg_ds_send = 0b00000000;
    if(_spi->setAndTestRegister(0x06, 1, &trg_ds_send)) {
        qFatal("TRG_DS Initialization failed!");
    } else {
        qDebug() << "TRG_DS initialized!";
        _state->setTRG_DS(trg_ds_send);
    }

    uint8_t trg_ts_send = 0b00000000;
    if(_spi->setAndTestRegister(0x07, 1, &trg_ts_send)) {
        qFatal("TRG_TS Initialization failed!");
    } else {
        qDebug() << "TRG_TS initialized!";
        _state->setTRG_TS(trg_ts_send);
    }
}

void Device::resetTVG()
{
    for(int j=0; j<8; j++) {
        uint8_t tvg[TVG_SAMPLES_BYTES];
        for(int i=0; i<TVG_SAMPLES_BYTES; i++) {
            tvg[i] = 0x00;
        }

        _spi->setRegister(0x40+j,TVG_SAMPLES_BYTES,tvg);
        if(checkConnection()) {
            qDebug() << "TVG for ch #" << j + 1 << "initialized!";
        } else {
            qDebug() << "TVG for ch #" << j + 1 << "not initialized!";
            qFatal("Initialization failed!");
        }
    }
}

void Device::resetChannelsTable()
{
    for(int j=0; j<8; j++) {
        for(int i=0; i<6; i++) {
            uint8_t temp = 0;
            if(_spi->setAndTestRegister(0x10+j*6+i,1,&temp)) {
                qDebug() << "Channels table for ch #" << j + 1 << "not initialized!";
                qFatal("Initialization failed!");
            }
        }
        qDebug() << "Channels table for ch #" << j + 1 << "initialized!";
        TactRegisters tact;
        tact._CR = 0;
        tact._PULSER1 = 0;
        tact._PULSER2 = 0;
        tact._RESERVED = 0;
        tact._TR1 = 0;
        tact._TR2 = 0;
        _state->setChannelsTableTact(j,tact);
    }
}

void Device::applyCalibration(DeviceMode *calibration)
{
    for(int j=0; j<calibration->getChannelsCount(); j++) {
        TVG tvg = calibration->getChannel(j)->rx()->generateTVG();
        _spi->setRegister(0x40+j,TVG_SAMPLES_BYTES,tvg._samples);
        if(checkConnection()) {
            qDebug() << "TVG for ch #" << j + 1 << " set!";
        } else {
            qDebug() << "TVG for ch #" << j + 1 << "not set!";
            qFatal("Initialization failed!");
        }
    }
    for(int j=0; j<MAX_TACTS_COUNT; j++) {
        TactRegisters tr = getRegistersByTact(j,calibration);//calibration->getTactRegistersByIndex(j);

        if(_spi->setAndTestRegister(0x10+j*6,1,&tr._CR)) {
            qFatal("Unable to set register");
        }

        if(_spi->setAndTestRegister(0x10+j*6+1,1,&tr._TR1)) {
            qFatal("Unable to set register");
        }

        if(_spi->setAndTestRegister(0x10+j*6+2,1,&tr._PULSER1)) {
            qFatal("Unable to set register");
        }

        if(_spi->setAndTestRegister(0x10+j*6+3,1,&tr._TR2)) {
            qFatal("Unable to set register");
        }

        if(_spi->setAndTestRegister(0x10+j*6+4,1,&tr._PULSER2)) {
            qFatal("Unable to set register");
        }

        if(_spi->setAndTestRegister(0x10+j*6+5,1,&tr._RESERVED)) {
            qFatal("Unable to set register");
        }

        qDebug() << "Channels table for ch #" << j + 1 << " loaded!";

        _state->setChannelsTableTact(j,tr);
    }

}

void Device::setProgTrigger(bool enabled)
{
    uint8_t val;
    if(enabled) {
        val = 0b00000001;
    } else {
        val = 0b00000000;
    }
    _spi->setRegister(0x05,1,&val);
    _state->setTRG_CR(val);
}

DeviceStatus Device::getDeviceStatus()
{
    DeviceStatus st;
    uint8_t stReg;
    _spi->getRegister(0x03,1,&stReg);
    _state->setUSM_SR(stReg);
    st.error = (stReg & 0b10000000) != 0;
    st.thsd = (stReg & 0b00001000) != 0;
    st.ready = (stReg & 0b00000001) != 0;
    return st;
}

void Device::setTVG(int chIndex, TVG tvg)
{
    _spi->setRegister(0x40 + chIndex,TVG_SAMPLES_BYTES,tvg._samples);
    _state->setTVGForChannel(chIndex,tvg);
}

AScan Device::getAscanForLine(uint8_t line, AScan * output)
{
    //AScan scan;
    uint8_t * buf = reinterpret_cast<uint8_t*>(output);
    //uint8_t buf[ASCAN_SAMPLES_SIZE + ASCAN_HEADER_SIZE];
    _spi->getRegister((line == 0) ? 0x7C : 0x7D, ASCAN_SAMPLES_SIZE + ASCAN_HEADER_SIZE, buf);

    /*scan._header._frameMarker = buf[0];
    scan._header._descriptorSizeInBytes = buf[1];
    scan._header._tactNo = buf[2];
    scan._header._channelNo = buf[3];
    scan._header._dataType = buf[4];
    scan._header._dataWidth = buf[5];
    uint16_t * sptr = reinterpret_cast<uint16_t*>(&(buf[6]));
    scan._header._samplesPerChannel = *sptr;
    uint64_t * odoptr = reinterpret_cast<uint64_t*>(&(buf[8]));
    scan._header._odoStamp = *odoptr;

    for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        scan._samples[i] = buf[i + ASCAN_HEADER_SIZE];
    }
*/
    if(!checkConnection()) {
        qFatal("Connection lost after Ascan request!");
    }

    return *(reinterpret_cast<AScan*>(buf));
}

uint8_t Device::getVersion()
{
    uint8_t version = 0;
    _spi->getRegister(0x02,1,&version);
    return version;
}

bool Device::checkConnection()
{
    uint8_t zero = 0;
    uint8_t ff = 0;
    _spi->getRegister(0x00,1,&zero);
    _spi->getRegister(0x01,1,&ff);
    return (ff == 0xff) && (zero == 0x00);
}

bool Device::getErrorFlag() const
{
    return _spi->getErrorFlag();
}

