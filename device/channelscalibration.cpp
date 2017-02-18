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

}

ChannelsCalibration::~ChannelsCalibration()
{
    qDebug() << "Device calibration deleted";

    for(int i=0; i<_channels.size(); i++) {
        delete _channels.at(i);
    }
}

void ChannelsCalibration::init()
{

}

ChannelsCalibration::ChannelsCalibration(ChannelsCalibration *original)
{
    for(int i=0;i<original->getChannelsCount();i++) {
        Channel * orig = original->getChannel(i);
        Channel * ch = new Channel(*orig);
        _channels.push_back(ch);
    }
}

ChannelsCalibration * ChannelsCalibration::getSnapshot()
{
    return new ChannelsCalibration(this);
}

Channel *ChannelsCalibration::getChannel(int index)
{
    return _channels.at(index);
}

uint8_t ChannelsCalibration::getChannelsCount()
{
    return _channels.size();
}
