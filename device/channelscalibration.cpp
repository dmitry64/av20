#include "channelscalibration.h"


#include <QDebug>


uint16_t ChannelsCalibration::getTactId() const
{
    return _tactId;
}

void ChannelsCalibration::setTactId(const uint16_t &tactId)
{
    _tactId = tactId;
}

void ChannelsCalibration::setChannels(const std::vector<Channel *> &channels)
{
    _channels = channels;
}

ChannelsCalibration::ChannelsCalibration()
{
    _tactId = 0;
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
}

ChannelsCalibration * ChannelsCalibration::getSnapshot()
{
    return new ChannelsCalibration(this);
}

Channel *ChannelsCalibration::getChannel(int index)
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
