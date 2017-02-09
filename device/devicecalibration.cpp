#include "devicecalibration.h"

DeviceCalibration::DeviceCalibration()
{

}

void DeviceCalibration::init()
{
    for(int i=0;i<MAX_CHANNELS_COUNT; i++) {
        Channel * ch = new Channel(i);
        ch->setBaseSensLevel(16 + i);
        ch->setTvgMode(TVGMode::CurveMode);
        _channels.push_back(ch);
    }
    for(int i=0;i<MAX_TACTS_COUNT; i++) {
        Tact * tact = new Tact();
        tact->setRx1(i);
        tact->setTx1(i);
        tact->setRx1Enabled(true);
        tact->setTx1Enabled(true);
        tact->setTactEnabled(true);
        _tactTable.push_back(tact);
    }
}

DeviceCalibration::DeviceCalibration(DeviceCalibration *original)
{
    for(int i=0;i<MAX_CHANNELS_COUNT;i++) {
        Channel * orig = original->getChannel(i);
        Channel * ch = new Channel(*orig);
        _channels.push_back(ch);
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