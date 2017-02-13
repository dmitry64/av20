#include "devicecalibration.h"
#include <QDebug>

std::vector<Channel *> DeviceCalibration::getChannels() const
{
    return _channels;
}

std::vector<Tact *> DeviceCalibration::getTactTable() const
{
    return _tactTable;
}

DeviceCalibration::DeviceCalibration()
{

}

DeviceCalibration::~DeviceCalibration()
{
    qDebug() << "Device calibration deleted";
    for(int i=0; i<_tactTable.size(); i++) {
        delete _tactTable.at(i);
    }
    for(int i=0; i<_channels.size(); i++) {
        delete _channels.at(i);
    }
    _tactTable.clear();
    _channels.clear();
}

void DeviceCalibration::init()
{
    for(int i=0;i<8; i++) {
        Channel * ch = new Channel();
        ch->setIndex(i);
        ch->setBaseSensLevel(72 + i);
        ch->setTvgMode(TVGMode::CurveMode);
        ch->setPrismTime(0);
        std::vector<Gate> gates;
        Gate g1;
        g1._start = 33;
        g1._finish = 172;
        g1._level = 50;
        g1._id = 0;

        switch (i) {
            case 0:
            ch->setColor(255,30,30);
            break;
            case 1:
            ch->setColor(30,255,30);
            break;
            case 2:
            ch->setColor(30,30,255);
            break;
            case 3:
            ch->setColor(255,255,30);
            break;
            case 4:
            ch->setColor(255,30,255);
            break;
            case 5:
            ch->setColor(30,255,255);
            break;
            case 6:
            ch->setColor(30,30,30);
            break;
            case 7:
            ch->setColor(255,255,255);
            break;
        }

        gates.push_back(g1);
        ch->setGates(gates);
        _channels.push_back(ch);
    }
    for(int i=0;i<MAX_TACTS_COUNT; i++) {
        Tact * tact = new Tact();
        tact->setRx1(i);
        tact->setTx1(i);
        //if(i<8) {
        tact->setRx1Enabled(true);
        tact->setTx1Enabled(true);
        tact->setTactEnabled(true);
        //}
        _tactTable.push_back(tact);
    }
}

DeviceCalibration::DeviceCalibration(DeviceCalibration *original)
{
    for(int i=0;i<original->getChannelsCount();i++) {
        Channel * orig = original->getChannel(i);
        Channel * ch = new Channel(*orig);
        _channels.push_back(ch);
    }
    for(int i=0;i<original->getTactTable().size();i++) {
        Tact * tact = original->getTactTable().at(i);
        Tact * tactNew = new Tact(*tact);
        _tactTable.push_back(tactNew);
    }
}

DeviceCalibration * DeviceCalibration::getSnapshot()
{
    return new DeviceCalibration(this);
}

Channel * DeviceCalibration::getChannel(int index)
{
    return _channels.at(index);
}

uint8_t DeviceCalibration::getMaxTacts()
{
    uint8_t num = 0;
    for(int i=0; i<MAX_TACTS_COUNT; i++) {
        if(_tactTable[i]->getTactEnabled()) {
            num++;
        }
    }
    return num;
}

uint8_t DeviceCalibration::getChannelsCount()
{
    return _channels.size();
}

uint8_t DeviceCalibration::getTactIndexByCounter(uint8_t counter)
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

std::vector< std::pair<uint8_t, uint8_t> > DeviceCalibration::getTactLines(uint8_t tactIndex)
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

TactRegisters DeviceCalibration::getTactRegistersByIndex(uint8_t index)
{
    return _tactTable[index]->getRegisters();
}
