#ifndef CHANNELCONFIGURATION_H
#define CHANNELCONFIGURATION_H

#include "device/channel.h"
#include <vector>

class ChannelConfiguration
{
    ModeConfiguration _mode;
    std::string _configurationName;
    std::vector<Channel *> _channels;
public:
    ChannelConfiguration();
    ChannelConfiguration(ChannelConfiguration * original);
    ~ChannelConfiguration();

    std::vector<Channel *> channels() const;
    void setChannels(const std::vector<Channel *> &channels);
    Channel * getChannel(uint8_t index);
    uint8_t getChannelsCount();
    void addChannel(Channel * chan);
    ModeConfiguration getMode() const;
    std::string getConfigurationName() const;
    void setConfigurationName(const std::string &configurationName);
};

#endif // CHANNELCONFIGURATION_H
