#ifndef DEVICECALIBRATION_H
#define DEVICECALIBRATION_H

#include <vector>
#include "tact.h"
#include "definitions.h"

class DeviceCalibration
{
    std::vector<Tact *> _tactTable;
    std::vector<Channel *> _channels;

public:
    DeviceCalibration();
    ~DeviceCalibration();
    void init();
    DeviceCalibration(DeviceCalibration * original);
    DeviceCalibration *getSnapshot();
    // get/set
    Channel *getChannel(int index);
    uint8_t getMaxTacts();
    uint8_t getChannelsCount();
    uint8_t getTactIndexByCounter(uint8_t counter);
    std::vector< std::pair<uint8_t, uint8_t> > getTactLines(uint8_t tactIndex);
    TactRegisters getTactRegistersByIndex(uint8_t index);
    std::vector<Channel *> getChannels() const;
    std::vector<Tact *> getTactTable() const;
};

#endif // DEVICECALIBRATION_H
