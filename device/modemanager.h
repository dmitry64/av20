#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include "device/devicemode.h"
#include <map>

class ModeManager
{
    std::vector<DeviceMode*> _modes;
    std::vector<ChannelConfiguration*> _configurations;
public:
    ModeManager();
    void init();
    DeviceMode * getDefaultMode();
    DeviceMode * getModeByModeType(ModeConfiguration mode);

    std::vector<ChannelConfiguration *> getConfigurations() const;
};

#endif // MODEMANAGER_H
