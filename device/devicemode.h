#ifndef CHANNELSCALIBRATION_H
#define CHANNELSCALIBRATION_H

#include <vector>
#include "tact/tact.h"
#include "device/definitions.h"
#include "device/channel/channel.h"
#include "device/tact/tacttable.h"

class ChannelsCalibration
{
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
    std::vector<Channel *> getChannels() const;
};

#endif // CHANNELSCALIBRATION_H
