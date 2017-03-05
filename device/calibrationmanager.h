#ifndef CALIBRATIONMANAGER_H
#define CALIBRATIONMANAGER_H

#include "channelscalibration.h"
#include "tactid.h"
#include <map>
#include <list>

class CalibrationManager
{
    std::map<TactID, std::vector<ChannelsCalibration> > _calibrations;
    void initSearchModeCalibration();
    void initHandModeCalibration();
public:
    CalibrationManager();
    void init();
    ChannelsCalibration getLastCalibrationByTactID(TactID id);
    std::vector<ChannelsCalibration> getCalibrationsByTactID(TactID id);
    std::vector<CalibrationInfo> getCalibrationsInfoByTactID(TactID id);
    void addCalibration(const ChannelsCalibration &calibration);
    void removeCalibration(const ChannelsCalibration &calibration);
    void applyChannelsModification(TactID id, CalibrationIndex index, ChannelID channelId, Channel channel);
};

#endif // CALIBRATIONMANAGER_H
