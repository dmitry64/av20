#ifndef RXCHANNEL_H
#define RXCHANNEL_H

#include "rxchannel.h"
#include "txchannel.h"
#include "displaychannel.h"

class Channel
{
    RxChannel _rx;
    TxChannel _tx;

    std::vector<DisplayChannel> _displayChannels;

    uint8_t _colorRed;
    uint8_t _colorGreen;
    uint8_t _colorBlue;

    uint8_t _index;
public:
    Channel();
    ~Channel();

    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    uint8_t getColorRed() const;
    uint8_t getColorGreen() const;
    uint8_t getColorBlue() const;
    uint8_t index() const;
    void setIndex(const uint8_t &index);
    RxChannel getRx() const;
    void setRx(const RxChannel &rx);
    TxChannel getTx() const;
    void setTx(const TxChannel &tx);
    std::vector<DisplayChannel> getDisplayChannels() const;
    void setDisplayChannels(const std::vector<DisplayChannel> &displayChannels);
};

#endif // RXCHANNEL_H
