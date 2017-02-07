#include "driverspi.h"

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

bool DriverSPI::getErrorFlag() const
{
    return _errorFlag;
}

DriverSPI::DriverSPI(QString device) :
    _device(device),
    _mode(0x00),
    _bits(8),
    _speed(50000),
    _csdelay(1000),
    _cschange(0),
    _errorFlag(false)
{
    //_mode |= SPI_CS_HIGH;
}

void DriverSPI::init()
{
    qDebug("Initializing SPI driver...");
    _deviceFD = open(_device.toStdString().c_str(), O_RDWR);
    int ret = 0;
    if (_deviceFD < 0)
        qFatal("can't open device");

    ret = ioctl(_deviceFD, SPI_IOC_WR_MODE, &_mode);
    if (ret == -1)
        qFatal("can't set spi mode");

    ret = ioctl(_deviceFD, SPI_IOC_RD_MODE, &_mode);
    if (ret == -1)
        qFatal("can't get spi mode");

    ret = ioctl(_deviceFD, SPI_IOC_WR_BITS_PER_WORD, &_bits);
    if (ret == -1)
        qFatal("can't set bits per word");

    ret = ioctl(_deviceFD, SPI_IOC_RD_BITS_PER_WORD, &_bits);
    if (ret == -1)
        qFatal("can't get bits per word");

    ret = ioctl(_deviceFD, SPI_IOC_WR_MAX_SPEED_HZ, &_speed);
    if (ret == -1)
        qFatal("can't set max speed hz");

    ret = ioctl(_deviceFD, SPI_IOC_RD_MAX_SPEED_HZ, &_speed);
    if (ret == -1)
        qFatal("can't get max speed hz");

    qDebug("SPI driver initialized.");
}

void DriverSPI::sendCommand(uint8_t commandByte, uint8_t length) {
    uint8_t tx[2] = { commandByte, length };
    uint8_t rx[2] = { 0, 0 };

    struct spi_ioc_transfer tr;
    tr.tx_buf = (unsigned long)tx;
    tr.rx_buf = (unsigned long)rx;
    tr.len = 2;
    tr.delay_usecs = _csdelay;
    tr.speed_hz = _speed;
    tr.bits_per_word = _bits;
    tr.cs_change = _cschange;
    tr.pad = 0x0000;
    tr.rx_nbits = 0x00;
    tr.tx_nbits = 0x00;

    //printf("[tx: 0x%02x len: 0x%02x]\n",tx[0],tx[1]);
    int ret = ioctl(_deviceFD, SPI_IOC_MESSAGE(1), &tr);
    //printf("[rx: 0x%02x rx+: 0x%02x]\n",rx[0],rx[1]);
    if (ret < 1)
        qFatal("can't send command message");
}

void DriverSPI::sendData(uint8_t length,const uint8_t * bufPtr) {
    uint8_t rx[4096];

    memset(rx,0x00,4096);

    struct spi_ioc_transfer tr;
    tr.tx_buf = (unsigned long)bufPtr;
    tr.rx_buf = (unsigned long)rx;
    tr.len = length;
    tr.delay_usecs = _csdelay;
    tr.speed_hz = _speed;
    tr.bits_per_word = _bits;
    tr.cs_change = _cschange;
    tr.pad = 0x0000;
    tr.rx_nbits = 0x00;
    tr.tx_nbits = 0x00;

    int ret = ioctl(_deviceFD, SPI_IOC_MESSAGE(1), &tr);

    if (ret < 1)
        qFatal("can't send command message");
}

void DriverSPI::recvData(uint32_t length, uint8_t * bufPtr) {
    uint8_t tx[4096];

    memset(tx,0x00,4096);

    struct spi_ioc_transfer tr;
    tr.tx_buf = (unsigned long)tx;
    tr.rx_buf = (unsigned long)bufPtr;
    tr.len = length;
    tr.delay_usecs = _csdelay;
    tr.speed_hz = _speed;
    tr.bits_per_word = _bits;
    tr.cs_change = _cschange;
    tr.pad = 0x0000;
    tr.rx_nbits = 0x00;
    tr.tx_nbits = 0x00;

    int ret = ioctl(_deviceFD, SPI_IOC_MESSAGE(1), &tr);

    if (ret < 1)
        qFatal("can't send command message");
}

void DriverSPI::getRegister(uint8_t reg, uint32_t length, uint8_t * dest) {
    uint8_t byteLength = 0;
    if(length>=255) {
        byteLength = 0xff;
    } else {
        byteLength = length;
    }
    sendCommand(reg,byteLength);

    memset(dest,0x00,length);

    recvData(length,dest);

    /*printf("Printing register length=%d reg=0x%02x:",length, reg);

    for (int ret = 0; ret < length; ret++) {
        if (!(ret % 32))
            puts("");
        printf("%.2X ", dest[ret]);
    }

    printf("\n");*/
}

void DriverSPI::setRegister(uint8_t reg,const uint32_t length, uint8_t * src) {
    uint8_t byteLength = 0;
    if(length>=255) {
        byteLength = 0xff;
    } else {
        byteLength = length;
    }

    sendCommand(reg | 0b10000000,byteLength);

    sendData(length,src);
}

bool DriverSPI::setAndTestRegister(uint8_t reg,const uint32_t length, uint8_t * src) {
    setRegister(reg,length,src);
    uint8_t result[length];
    getRegister(reg,length,result);
    bool status = false;
    for(uint32_t i=0; i<length; i++) {
        if(src[i]!=result[i]) {
            printf("======================Error!\n");
            _errorFlag = true;
            status = true;
        }
    }
    return status;
}

