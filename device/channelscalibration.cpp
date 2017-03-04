#include "channelscalibration.h"
#include <QDebug>


TactID ChannelsCalibration::getTactId() const
{
    return _tactId;
}

void ChannelsCalibration::setTactId(const TactID &tactId)
{
    _tactId = tactId;
}

void ChannelsCalibration::setChannels(const std::vector<Channel> &channels)
{
    _channels = channels;
}

CalibrationInfo ChannelsCalibration::getInfo() const
{
    return _info;
}

void ChannelsCalibration::setInfo(const CalibrationInfo &info)
{
    _info = info;
}

void ChannelsCalibration::setChannel(const ChannelID index, const Channel &channel)
{
    _channels[index] = channel;
}

ChannelsCalibration::ChannelsCalibration()
{
    _tactId = 0;
    _info._id = 0;
    _info._name = "none";
}

ChannelsCalibration::~ChannelsCalibration()
{
    //qDebug() << "Device calibration deleted";
}

void ChannelsCalibration::init()
{
}

ChannelsCalibration ChannelsCalibration::getSnapshot()
{
    return ChannelsCalibration(*this);
}

Channel ChannelsCalibration::getChannel(const ChannelID index) const
{
    Q_ASSERT(index<8);
    Q_ASSERT(_channels.size() > 0);
    return _channels.at(index);
}

DisplayChannel ChannelsCalibration::getDisplayChannel(const ChannelID chan, const DisplayChannelID disp) const
{
    ChannelsInfo info;
    info._channel = chan;
    info._displayChannel = disp;
    return getDisplayChannel(info);
}

DisplayChannel ChannelsCalibration::getDisplayChannel(const ChannelsInfo info) const
{
    const auto & channels = getChannel(info._channel).getDisplayChannels();
    return channels.at(info._displayChannel);
}

uint8_t ChannelsCalibration::getChannelsCount() const
{
    size_t size = _channels.size();
    Q_ASSERT(size <= 8);
    return size;
}
