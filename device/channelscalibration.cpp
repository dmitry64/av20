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

void ChannelsCalibration::setChannels(const std::vector<Channel *> &channels)
{
    _channels = channels;
}

CalibrationInfo ChannelsCalibration::getInfo() const
{
    return _info;
}

ChannelsCalibration::ChannelsCalibration()
{
    _tactId = 0;
    _info._id = 0;
    _info._name = "none";
}

ChannelsCalibration::~ChannelsCalibration()
{
    qDebug() << "Device calibration deleted";

    for(int i=0; i<_channels.size(); i++) {
        Channel * chan = _channels.at(i);
        Q_ASSERT(chan);
        delete chan;
    }
}

void ChannelsCalibration::init()
{
}

ChannelsCalibration::ChannelsCalibration(ChannelsCalibration *original)
{
    Q_ASSERT(original);
    _tactId = original->getTactId();
    for(int i=0;i<original->getChannelsCount();i++) {
        Channel * ch = new Channel(original->getChannel(i));
        _channels.push_back(ch);
    }
    _info = original->getInfo();
}

ChannelsCalibration * ChannelsCalibration::getSnapshot()
{
    return new ChannelsCalibration(this);
}

Channel *ChannelsCalibration::getChannel(ChannelID index)
{
    Q_ASSERT(index<8);
    Q_ASSERT(_channels.size() > 0);
    return _channels.at(index);
}

uint8_t ChannelsCalibration::getChannelsCount()
{
    size_t size = _channels.size();
    Q_ASSERT(size <= 8);
    return size;
}
