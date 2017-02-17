#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include "devicemode.h"
#include "device/channelscalibration.h"
#include <map>

class ModeManager
{
    std::vector<DeviceMode *> _modes;
private:
    DeviceMode * generateSearchMode();
    DeviceMode * generateHandMode();
public:
    ModeManager();
    void init();
    std::vector<DeviceMode *> modes() const;
};

#endif // MODEMANAGER_H
