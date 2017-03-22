#include "channel.h"
#include <QDebug>

uint8_t Channel::index() const
{
    return _index;
}

void Channel::setIndex(const uint8_t &index)
{
    _index = index;
}

std::vector<DisplayChannel> Channel::getDisplayChannels() const
{
    return _displayChannels;
}

void Channel::setDisplayChannels(const std::vector<DisplayChannel> &displayChannels)
{
    _displayChannels = displayChannels;
}

uint8_t Channel::getActiveDisplayChannelIndex() const
{
    return _activeDisplayChannel;
}

void Channel::setActiveDisplayChannelIndex(const uint8_t &activeDisplayChannel)
{
    _activeDisplayChannel = activeDisplayChannel;
}

DisplayChannel Channel::getActiveDisplayChannel() const
{
    return _displayChannels[_activeDisplayChannel];
}

Channel::Channel() : _colorRed(0), _colorGreen(0), _colorBlue(0), _index(0), _activeDisplayChannel(0)
{
}

Channel::~Channel()
{

}

QDomElement Channel::generateXML(QDomDocument &doc) const
{
    QDomElement channel = doc.createElement("channel");

    QDomElement index = doc.createElement("id");
    index.appendChild(doc.createTextNode(QString::number(_index)));
    channel.appendChild(index);

    QDomElement color = doc.createElement("color");
    color.appendChild(doc.createElement("red")).appendChild(doc.createTextNode(QString::number(_colorRed)));
    color.appendChild(doc.createElement("green")).appendChild(doc.createTextNode(QString::number(_colorGreen)));
    color.appendChild(doc.createElement("blue")).appendChild(doc.createTextNode(QString::number(_colorBlue)));
    channel.appendChild(color);

    QDomElement dispChannels = doc.createElement("displayChannels");
    for(auto it = _displayChannels.begin(); it!=_displayChannels.end(); it++) {
        const DisplayChannel & dc = it.operator *();
        QDomElement dispChan = dc.generateXML(doc);
        dispChannels.appendChild(dispChan);
    }
    channel.appendChild(dispChannels);


    return channel;
}

void Channel::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    _colorRed = red;
    _colorBlue = blue;
    _colorGreen = green;
}

uint8_t Channel::getColorRed() const
{
    return _colorRed;
}

uint8_t Channel::getColorGreen() const
{
    return _colorGreen;
}

uint8_t Channel::getColorBlue() const
{
    return _colorBlue;
}
