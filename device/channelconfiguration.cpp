#include "channelconfiguration.h"

std::vector<Channel *> ChannelConfiguration::channels() const
{
    return _channels;
}

void ChannelConfiguration::setChannels(const std::vector<Channel *> &channels)
{
    _channels = channels;
}

Channel *ChannelConfiguration::getChannel(uint8_t index)
{
    return _channels.at(index);
}

uint8_t ChannelConfiguration::getChannelsCount()
{
    return _channels.size();
}

void ChannelConfiguration::addChannel(Channel *chan)
{
    _channels.push_back(chan);
}

ModeConfiguration ChannelConfiguration::getMode() const
{
    return _mode;
}

std::string ChannelConfiguration::getConfigurationName() const
{
    return _configurationName;
}

void ChannelConfiguration::setConfigurationName(const std::string &configurationName)
{
    _configurationName = configurationName;
}

ChannelConfiguration::ChannelConfiguration()
{
    _mode = ModeConfiguration::Mode8Ch;
}

ChannelConfiguration::ChannelConfiguration(ChannelConfiguration * original)
{
    for(int i=0;i<original->getChannelsCount();i++) {
        Channel * orig = original->getChannel(i);
        Channel * ch = new Channel(*orig);
        _channels.push_back(ch);
    }
}

ChannelConfiguration::~ChannelConfiguration()
{
    for(int i=0; i<_channels.size(); i++) {
        delete _channels.at(i);
    }
}
