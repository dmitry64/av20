#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include "devicemode.h"
#include "device/channelscalibration.h"
#include <map>

class ModeManager
{
    std::vector<DeviceMode> _modes;
private:
    static DeviceMode generateSearchMode();
    static DeviceMode generateHandMode();
    static std::vector<Tact> generateSearchTacts(int tactsNumber);

    static TactTable generateSearchTable(TactID tact, int tactsNumber,  const QString &name);

public:
    ModeManager();
    void init();
    std::vector<DeviceMode> modes() const;
    void addMode(const DeviceMode &mode);

};

#endif // MODEMANAGER_H
