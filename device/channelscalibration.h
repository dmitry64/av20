#ifndef CHANNELSCALIBRATION_H
#define CHANNELSCALIBRATION_H

#include <vector>
#include <QtXml/QDomDocument>
#include "tact/tact.h"
#include "device/definitions.h"
#include "device/channel/channel.h"
#include "device/tact/tacttable.h"

class ChannelsCalibration
{
    TactID _tactId;
    CalibrationInfo _info;
    std::vector<Channel> _channels;
    bool _active;
public:
    ChannelsCalibration();
    ~ChannelsCalibration();
    void saveToFile(QString path,size_t saveIndex) const;
    void loadFromFile(QString path, size_t index);
    QDomDocument generateXML(size_t newIndex) const;
    //void init();
    ChannelsCalibration getSnapshot();
    // get/set
    Channel getChannel(const ChannelID index) const;
    DisplayChannel getDisplayChannel(const ChannelID chan, const DisplayChannelID disp) const;
    DisplayChannel getDisplayChannel(const ChannelsInfo & info) const;
    uint8_t getChannelsCount() const;
    TactID getTactId() const;
    void setTactId(const TactID &tactId);
    void setChannels(const std::vector<Channel> &channels);
    CalibrationInfo getInfo() const;
    void setInfo(const CalibrationInfo &info);
    void setChannel(const ChannelID index,const Channel & channel);
    bool getActive() const;
    void setActive(bool active);
};

#endif // CHANNELSCALIBRATION_H
