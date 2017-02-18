#ifndef CHANNELSCALIBRATION_H
#define CHANNELSCALIBRATION_H

#include <vector>
#include "tact/tact.h"
#include "device/definitions.h"
#include "device/channel/channel.h"
#include "device/tact/tacttable.h"

class ChannelsCalibration
{
    uint16_t _tactId;
    std::vector<Channel *> _channels;

public:
    ChannelsCalibration();
    ~ChannelsCalibration();
    void init();
    ChannelsCalibration(ChannelsCalibration *original);
    ChannelsCalibration *getSnapshot();
    // get/set
    Channel *getChannel(int index);
    uint8_t getChannelsCount();
    uint16_t getTactId() const;
    void setTactId(const uint16_t &tactId);
    void setChannels(const std::vector<Channel *> &channels);
};

#endif // CHANNELSCALIBRATION_H
