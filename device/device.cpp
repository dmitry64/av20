#include "device.h"
#include <QDebug>

Device::Device(DeviceState *state) : _spi(new DriverSPI("/dev/spidev0.0")), _state(state)
{

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
        uint8_t tvg[150];
        for(int i=0; i<150; i++) {
            tvg[i] = 0x00;
        }

        _spi->setRegister(0x40+j,150,tvg);
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
        Tact tact;
        tact._CR = 0;
        tact._PULSER1 = 0;
        tact._PULSER2 = 0;
        tact._RESERVED = 0;
        tact._TR1 = 0;
        tact._TR2 = 0;
        _state->setChannelsTableTact(j,tact);
    }
}
/*
void setBit(uint8_t * ptr, int bit, uint8_t val) {
    uint8_t prev = ptr[bit/8];
    ptr[bit/8] |= (((prev >> (bit % 8)) & val) << (bit % 8));
}

void Device::setTVG(int chIndex, std::vector<uint8_t> values8bit)
{
    uint8_t packedValues[TVG_SAMPLES_BYTES];
    for(int i=0; i<values8bit.size(); i++) {
        for(int j=0; j<6; j++) {
            setBit(packedValues,i*6 + j, (values8bit[i] >> j) & 0b00000001);
        }
    }
    _spi->setRegister(0x40 + chIndex,TVG_SAMPLES_BYTES,packedValues);
}*/

AScan Device::getAscanForChannel(uint8_t activeChannel)
{
    AScan scan;
    uint8_t buf[ASCAN_SAMPLES_SIZE + ASCAN_HEADER_SIZE];
    _spi->getRegister((activeChannel == 1) ? 0x7C : 0x7D, ASCAN_SAMPLES_SIZE + ASCAN_HEADER_SIZE, buf);

    scan._header._frameMarker = buf[0];
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

    if(!checkConnection()) {
        qFatal("Connection lost after Ascan request!");
    }

    return scan;
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

