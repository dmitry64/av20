#include "devicemode.h"
#include "tvg/tvgsinglepoint.h"

#include <QDebug>


std::vector<Channel *> DeviceMode::getChannels() const
{
    return _channelConfiguration->channels();
}

std::vector<Tact *> DeviceMode::getTactTable() const
{
    return _tactTable;
}

ChannelConfiguration *DeviceMode::getChannelConfiguration() const
{
    return _channelConfiguration;
}

void DeviceMode::setChannelConfiguration(ChannelConfiguration *channelConfiguration)
{
    _channelConfiguration = channelConfiguration;
}

ModeConfiguration DeviceMode::getMode() const
{
    return _mode;
}

DeviceMode::DeviceMode()
{
    _mode = ModeConfiguration::Mode8Ch;
    _channelConfiguration = 0;
}

DeviceMode::~DeviceMode()
{
    qDebug() << "Device calibration deleted";
    for(int i=0; i<_tactTable.size(); i++) {
        delete _tactTable.at(i);
    }

    _tactTable.clear();

    delete _channelConfiguration;
}

void DeviceMode::init()
{
        _channelConfiguration = new ChannelConfiguration();

        for(int i=0;i<8; i++) {
            Channel * chTemp = new Channel();
            RxChannel * rx = new RxChannel();
            TxChannel * tx = new TxChannel();
            chTemp->setRx(rx);
            chTemp->setTx(tx);

            tx->setFreq(PulserFreq::Freq_2_5_MHz);
            tx->setProg(PulserProg::Prog_1);

            chTemp->setIndex(i);
            //rx->setBaseSensLevel(72 + i);
            //rx->setTvgMode(TVGMode::CurveMode);
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

            _channelConfiguration->addChannel(chTemp);
        }

        for(int i=0;i<MAX_TACTS_COUNT; i++) {
            Tact * tact = new Tact();
            tact->setRx1(i);
            tact->setTx1(i);

            if(i<8) {
            tact->setRx1Enabled(true);
            tact->setTx1Enabled(true);
            tact->setTactEnabled(true);
            } else {
                tact->setRx1Enabled(false);
                tact->setTx1Enabled(false);
                tact->setTactEnabled(false);
            }

            _tactTable.push_back(tact);
        }
}

DeviceMode::DeviceMode(DeviceMode *original)
{
    _channelConfiguration = new ChannelConfiguration(original->_channelConfiguration);
    for(int i=0;i<original->getTactTable().size();i++) {
        Tact * tact = original->getTactTable().at(i);
        Tact * tactNew = new Tact(*tact);
        _tactTable.push_back(tactNew);
    }
}

DeviceMode * DeviceMode::getSnapshot()
{
    return new DeviceMode(this);
}

Channel *DeviceMode::getChannel(int index)
{
    return _channelConfiguration->getChannel(index);
}

uint8_t DeviceMode::getMaxTacts()
{
    uint8_t num = 0;
    for(int i=0; i<MAX_TACTS_COUNT; i++) {
        if(_tactTable[i]->getTactEnabled()) {
            num++;
        }
    }
    return num;
}

uint8_t DeviceMode::getChannelsCount()
{
    return _channelConfiguration->getChannelsCount();
}

uint8_t DeviceMode::getTactIndexByCounter(uint8_t counter)
{
    uint8_t num = 0;
    for(int i=0; i<MAX_TACTS_COUNT; i++) {
        if(_tactTable[i]->getTactEnabled()) {
            if(counter == num) {
                return i;
            }
            num++;
        }
    }
    return 0;
}

std::vector< std::pair<uint8_t, uint8_t> > DeviceMode::getTactLines(uint8_t tactIndex)
{
    std::vector< std::pair<uint8_t, uint8_t> > lines;

    Tact * tact = _tactTable.at(tactIndex);
    if(tact->getRx1Enabled()) {
        std::pair<uint8_t, uint8_t> p1(0,tact->getRx1());
        lines.push_back(p1);
    }
    if(tact->getRx2Enabled()) {
        std::pair<uint8_t, uint8_t> p2(1,tact->getRx2());
        lines.push_back(p2);
    }

    return lines;
}

Tact *DeviceMode::getTactByIndex(uint8_t index)
{
    return _tactTable[index];
}

//TactRegisters DeviceMode::getTactRegistersByIndex(uint8_t index)
//{
//    return _tactTable[index]->getRegisters();
//}
