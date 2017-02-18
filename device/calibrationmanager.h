#ifndef CALIBRATIONMANAGER_H
#define CALIBRATIONMANAGER_H

#include "channelscalibration.h"
#include "tactid.h"
#include <map>
#include <list>

class CalibrationManager
{
    std::map<uint16_t, std::list<ChannelsCalibration*> * > _calibrations;
    void initSearchModeCalibration();
    void initHandModeCalibration();
public:
    CalibrationManager();
    void init();
    ChannelsCalibration * getLastCalibrationByTactID(uint16_t id);
    std::vector<ChannelsCalibration *> getCalibrationsByTactID(uint16_t id);
    void addCalibration(ChannelsCalibration * calibration);
    void removeCalibration(ChannelsCalibration * calibration);
};

#endif // CALIBRATIONMANAGER_H
