#ifndef CALIBRATIONMANAGER_H
#define CALIBRATIONMANAGER_H

#include "channelscalibration.h"
#include "tactid.h"
#include "common/commonfunctions.h"
#include <map>
#include <list>

#include <QString>

class CalibrationManager
{
    std::map<TactID, std::vector<ChannelsCalibration> > _calibrations;
    QString _savePath;
    void initSearchModeCalibration();
    void initHandModeCalibration();
    void syncWithFile(const ChannelsCalibration &calib) const;
    void sortCalibrations();
public:
    CalibrationManager();
    ~CalibrationManager();
    void saveAll();
    void loadAll();
    void setSavePath(const QString & path);
    void init();
    ChannelsCalibration getLastCalibrationByTactID(TactID id);
    std::vector<ChannelsCalibration> getCalibrationsByTactID(TactID id);
    std::vector<CalibrationInfo> getCalibrationsInfoByTactID(TactID id);
    void addCalibration(const ChannelsCalibration &calibration);
    void removeCalibration(TactID id, const CalibrationIndex index);
    void createCopyCalibration(TactID id, CalibrationIndex index, const QString &name);
    void applyChannelsModification(TactID id, CalibrationIndex index, ChannelID channelId,const Channel & channel);
private:
    static std::vector<Gate> generateGates();
    static void setColor(Channel &chTemp, int i);
    static DisplayChannel generateDisplayChannel(const double angle);
    std::vector<Channel> generateChannels(int channelsNumber, int dispChansNumber);
    ChannelsCalibration generateCalibration(TactID tact, CalibrationIndex index, const QString &name, int channelsNumber, int dispChansNumber);
};

#endif // CALIBRATIONMANAGER_H
