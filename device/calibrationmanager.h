#ifndef CALIBRATIONMANAGER_H
#define CALIBRATIONMANAGER_H

#include "channelscalibration.h"
#include "tactid.h"
#include "commonfunctions.h"
#include <map>
#include <list>

#include <QString>

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
    void removeCalibration(TactID id, const CalibrationIndex index);
    void createCopyCalibration(TactID id, CalibrationIndex index, QString name);
    void applyChannelsModification(TactID id, CalibrationIndex index, ChannelID channelId, Channel channel);
private:
    std::vector<Gate> generateGates();
    void setColor(Channel &chTemp, int i);
    DisplayChannel generateDisplayChannel(double angle);
    std::vector<Channel> generateChannels(int channelsNumber, int dispChansNumber);
    ChannelsCalibration generateCalibration(TactID tact, CalibrationIndex index, QString name, int channelsNumber, int dispChansNumber);
};

#endif // CALIBRATIONMANAGER_H
