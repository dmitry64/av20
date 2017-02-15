#ifndef RXCHANNEL_H
#define RXCHANNEL_H

#include "device/rxchannel.h"
#include "device/txchannel.h"


class Channel
{
    RxChannel * _rx;
    TxChannel * _tx;


    uint8_t _colorRed;
    uint8_t _colorGreen;
    uint8_t _colorBlue;

    uint8_t _index;
public:
    Channel();

    RxChannel *rx() const;
    void setRx(RxChannel *rx);
    TxChannel *tx() const;
    void setTx(TxChannel *tx);
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    uint8_t getColorRed();
    uint8_t getColorGreen();
    uint8_t getColorBlue();
    uint8_t index() const;
    void setIndex(const uint8_t &index);
};

#endif // RXCHANNEL_H
