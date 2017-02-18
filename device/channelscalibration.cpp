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
    /*for(int i=0;i<8; i++) {
        Channel * chTemp = new Channel();
        RxChannel * rx = new RxChannel();
        TxChannel * tx = new TxChannel();
        chTemp->setRx(rx);
        chTemp->setTx(tx);

        tx->setFreq(PulserFreq::Freq_2_5_MHz);
        tx->setProg(PulserProg::Prog_1);

        chTemp->setIndex(i);
        rx->setTvgCurve(new TVGSinglePoint(1));
        rx->setPrismTime(0);
        std::vector<Gate> gates;
        Gate g1;
        g1._start = 33;
        g1._finish = 172;
        g1._level = 50;
        g1._id = 0;
        gates.push_back(g1);
        rx->setGates(gates);

        switch (i) {
            case 0:
            chTemp->setColor(255,30,30);
            break;
            case 1:
            chTemp->setColor(30,255,30);
            break;
            case 2:
            chTemp->setColor(255,30,255);
            break;
            case 3:
            chTemp->setColor(255,128,128);
            break;
            case 4:
            chTemp->setColor(255,255,30);
            break;
            case 5:
            chTemp->setColor(30,255,255);
            break;
            case 6:
            chTemp->setColor(128,128,255);
            break;
            case 7:
            chTemp->setColor(30,30,255);
            break;
        }

        rx->setName("58");

        _channels.push_back(chTemp);
    }*/
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
