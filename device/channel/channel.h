#ifndef RXCHANNEL_H
#define RXCHANNEL_H


#include "displaychannel.h"

class Channel
{
    std::vector<DisplayChannel> _displayChannels;

    uint8_t _colorRed;
    uint8_t _colorGreen;
    uint8_t _colorBlue;

    ChannelID _index;
    uint8_t _activeDisplayChannel;
public:
    Channel();
    ~Channel();

    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    uint8_t getColorRed() const;
    uint8_t getColorGreen() const;
    uint8_t getColorBlue() const;
    uint8_t index() const;
    void setIndex(const uint8_t &index);
    std::vector<DisplayChannel> getDisplayChannels() const;
    void setDisplayChannels(const std::vector<DisplayChannel> &displayChannels);
    uint8_t getActiveDisplayChannelIndex() const;
    void setActiveDisplayChannelIndex(const uint8_t &activeDisplayChannel);
    DisplayChannel getActiveDisplayChannel() const;
};

#endif // RXCHANNEL_H
