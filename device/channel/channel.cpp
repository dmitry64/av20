#include "channel.h"
#include <QDebug>

RxChannel *Channel::rx() const
{
    return _rx;
}

void Channel::setRx(RxChannel *rx)
{
    _rx = rx;
}

TxChannel *Channel::tx() const
{
    return _tx;
}

void Channel::setTx(TxChannel *tx)
{
    _tx = tx;
}

uint8_t Channel::index() const
{
    return _index;
}

void Channel::setIndex(const uint8_t &index)
{
    _index = index;
}

Channel::Channel() : _rx(0), _tx(0), _colorRed(0), _colorGreen(0), _colorBlue(0)
{
}

Channel::~Channel()
{
    Q_ASSERT(_rx);
    Q_ASSERT(_tx);
    delete _rx;
    delete _tx;
}

Channel::Channel(Channel *channel)
{
    Q_ASSERT(channel);
    _colorRed = channel->getColorRed();
    _colorGreen = channel->getColorGreen();
    _colorBlue = channel->getColorBlue();
    _index = channel->index();
    _rx = new RxChannel(channel->rx());
    _tx = new TxChannel(channel->tx());
}


void Channel::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    _colorRed = red;
    _colorBlue = blue;
    _colorGreen = green;
}

uint8_t Channel::getColorRed()
{
    return _colorRed;
}

uint8_t Channel::getColorGreen()
{
    return _colorGreen;
}

uint8_t Channel::getColorBlue()
{
    return _colorBlue;
}
