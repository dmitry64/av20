#include "device.h"
#include <QDebug>
#define FAKESPI

TactRegisters Device::getRegistersByTact(uint8_t index, ChannelsCalibration * mode, TactTable * tactTable)
{
    Q_ASSERT(index < 8);
    Q_ASSERT(mode);
    Q_ASSERT(tactTable);
    Tact * tact = tactTable->getTactByIndex(index);
    Q_ASSERT(tact);

    TactRegisters reg;

    reg._CR = 0x00;
    reg._CR |= ((tact->getDiffMode() & 0b00000001) << 1);
    reg._CR |= (tact->getTactEnabled() & 0b00000001);

    reg._TR1 = 0x00;
    reg._TR1 |= ((tact->getRx1Enabled() & 0b00000001) << 7);
    reg._TR1 |= ((tact->getRx1() & 0b00000111) << 4);
    reg._TR1 |= ((tact->getTx1Enabled() & 0b00000001) << 3);
    reg._TR1 |= (tact->getTx1() & 0b00000111);

    TxChannel * firstTx = mode->getChannel(tact->getTx1())->tx();
    Q_ASSERT(firstTx);
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
    Q_ASSERT(secondTx);
    reg._PULSER2 = 0x00;
    reg._PULSER2 |= ((secondTx->doubleMode() & 0b00000001) << 7);
    uint8_t prog2 = secondTx->prog();
    reg._PULSER1 |= ((prog2 & 0b00001111) << 3);
    uint8_t freq2 = secondTx->freq();
    reg._PULSER2 |= (freq2 & 0b00001111);

    reg._RESERVED = 0x00;

    return reg;
}



TVG Device::getTVGFromCurve(TVGCurve *curve)
{
    Q_ASSERT(curve);

    uint8_t packedValues[TVG_SAMPLES_BYTES];
    memset(packedValues,0,TVG_SAMPLES_BYTES);
    for(int i=0; i<TVG_SAMPLES_SIZE; i++) {
        double sample = curve->getSample(static_cast<double>(i) / TVG_SAMPLES_SIZE);

        uint8_t value = qRound(sample * TVG_MAX_DB);
        Q_ASSERT(value <= TVG_MAX_DB);
        for(int j=0; j<7; j++) {
            setBit(packedValues,i*7 + j, (value >> j) & 0b00000001);
        }
    }

    TVG tvg;

    for(int i=0; i<TVG_SAMPLES_BYTES; i++) {
        tvg._samples[i] = packedValues[i];
    }

    return tvg;
}

Device::Device()
{
#ifdef FAKESPI
    _spi = new FakeSPI();
#else
    _spi = new DriverSPI("/dev/spidev0.0");
#endif
    Q_ASSERT(_spi);
}

void Device::init()
{
    _spi->init();
    bool status = checkConnection();

    if(status) {
        uint8_t version = getVersion();
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
    }

    uint8_t trg_ds_send = 0b00000000;
    if(_spi->setAndTestRegister(0x06, 1, &trg_ds_send)) {
        qFatal("TRG_DS Initialization failed!");
    }

    uint8_t trg_ts_send = 0b00000000;
    if(_spi->setAndTestRegister(0x07, 1, &trg_ts_send)) {
        qFatal("TRG_TS Initialization failed!");
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
           // qDebug() << "TVG for ch #" << j + 1 << "initialized!";
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
        TactRegisters tact;
        tact._CR = 0;
        tact._PULSER1 = 0;
        tact._PULSER2 = 0;
        tact._RESERVED = 0;
        tact._TR1 = 0;
        tact._TR2 = 0;
        setTact(tact,j);
    }
}

void Device::resetDevice()
{
    resetConfigRegisters();
    resetChannelsTable();
    resetTVG();
}

void Device::applyCalibration(ChannelsCalibration *calibration, TactTable *tactTable)
{
    Q_ASSERT(calibration);
    Q_ASSERT(tactTable);

    for(int j=0; j<calibration->getChannelsCount(); j++) {
        Channel * chan = calibration->getChannel(j);
        Q_ASSERT(chan);
        RxChannel * rxchan = chan->rx();
        Q_ASSERT(rxchan);
        TVGCurve * curve = rxchan->getTvgCurve();
        Q_ASSERT(curve);
        TVG tvg = getTVGFromCurve(curve);
        _spi->setRegister(0x40+j,TVG_SAMPLES_BYTES,tvg._samples);
        if(checkConnection()) {
           // qDebug() << "TVG for ch #" << j + 1 << " set!";
        } else {
            qDebug() << "TVG for ch #" << j + 1 << "not set!";
            qFatal("Initialization failed!");
        }
    }
    for(int k=0; k<tactTable->getMaxTacts(); k++) {
        TactIndex j = tactTable->getTactIndexByCounter(k);
        TactRegisters tr = getRegistersByTact(j,calibration,tactTable);
        setTact(tr,j);
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
}

DeviceStatus Device::getDeviceStatus()
{
    DeviceStatus st;
    uint8_t stReg;
    _spi->getRegister(0x03,1,&stReg);
    //_state->setUSM_SR(stReg);
    st.error = (stReg & 0b10000000) != 0;
    st.thsd = (stReg & 0b00001000) != 0;
    st.ready = (stReg & 0b00000001) != 0;
    return st;
}

void Device::setTVG(int chIndex, TVG tvg)
{
    Q_ASSERT(chIndex < 8);
    _spi->setRegister(0x40 + chIndex,TVG_SAMPLES_BYTES,tvg._samples);
    //_state->setTVGForChannel(chIndex,tvg);
}

void Device::setTact(TactRegisters reg, TactIndex index)
{
    Q_ASSERT(index<8);
    if(_spi->setAndTestRegister(0x10+index*6,1,&reg._CR)) {
        Q_ASSERT(false);
    }
    if(_spi->setAndTestRegister(0x10+index*6+1,1,&reg._TR1)) {
        Q_ASSERT(false);
    }
    if(_spi->setAndTestRegister(0x10+index*6+2,1,&reg._PULSER1)){
        Q_ASSERT(false);
    }
    if(_spi->setAndTestRegister(0x10+index*6+3,1,&reg._TR2)){
        Q_ASSERT(false);
    }
    if(_spi->setAndTestRegister(0x10+index*6+4,1,&reg._PULSER2)){
        Q_ASSERT(false);
    }
    if(_spi->setAndTestRegister(0x10+index*6+5,1,&reg._RESERVED)){
        Q_ASSERT(false);
    }

}

AScan Device::getAscanForLine(uint8_t line, AScan * output)
{
    Q_ASSERT(output);
    Q_ASSERT(line==0 || line==1);
    uint8_t * buf = reinterpret_cast<uint8_t*>(output);
    _spi->getRegister((line == 0) ? 0x7C : 0x7D, ASCAN_SAMPLES_SIZE + ASCAN_HEADER_SIZE, buf);

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

