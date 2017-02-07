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

uint8_t * Device::getAscanForChannel(uint8_t activeChannel)
{
    uint8_t buf[800];
    switch (activeChannel) {
    case 0:
        _spi->getRegister(0x7C, 800, buf);
        for(int i=0; i<800; i++)
            _state->getAscanForChannel(0)[i] = buf[i];
        return _state->getAscanForChannel(0);
    case 1:
        _spi->getRegister(0x7D, 800, buf);
        for(int i=0; i<800; i++)
            _state->getAscanForChannel(1)[i] = buf[i];
        return _state->getAscanForChannel(1);
    default:
        break;
    }

    /*if(!checkConnection()) {
        qFatal("Connection lost after Ascan request!");
    }*/
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

