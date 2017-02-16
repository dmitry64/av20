#ifndef DEVICEMODE_H
#define DEVICEMODE_H

#include <vector>
#include "tact.h"
#include "definitions.h"
#include "channel.h"

class DeviceMode
{
    ModeConfiguration _mode;
    std::vector<Tact *> _tactTable;
    std::vector<Channel *> _channels;

public:
    DeviceMode();
    ~DeviceMode();
    void init();
    DeviceMode(DeviceMode *original);
    DeviceMode *getSnapshot();
    // get/set
    Channel *getChannel(int index);
    uint8_t getMaxTacts();
    uint8_t getChannelsCount();
    uint8_t getTactIndexByCounter(uint8_t counter);
    std::vector< std::pair<uint8_t, uint8_t> > getTactLines(uint8_t tactIndex);
    Tact * getTactByIndex(uint8_t index);
    std::vector<Channel *> getChannels() const;
    std::vector<Tact *> getTactTable() const;
    ModeConfiguration getMode() const;
};

#endif // DEVICEMODE_H
