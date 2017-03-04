#ifndef CHANNELSCALIBRATION_H
#define CHANNELSCALIBRATION_H

#include <vector>
#include "tact/tact.h"
#include "device/definitions.h"
#include "device/channel/channel.h"
#include "device/tact/tacttable.h"

class ChannelsCalibration
{
    TactID _tactId;
    CalibrationInfo _info;
    std::vector<Channel> _channels;

public:
    ChannelsCalibration();
    ~ChannelsCalibration();
    void init();
    ChannelsCalibration getSnapshot();
    // get/set
    Channel getChannel(const ChannelID index) const;
    DisplayChannel getDisplayChannel(const ChannelID chan, const DisplayChannelID disp) const;
    DisplayChannel getDisplayChannel(const ChannelsInfo info) const;
    uint8_t getChannelsCount() const;
    TactID getTactId() const;
    void setTactId(const TactID &tactId);
    void setChannels(const std::vector<Channel> &channels);
    CalibrationInfo getInfo() const;
    void setInfo(const CalibrationInfo &info);
};

#endif // CHANNELSCALIBRATION_H
