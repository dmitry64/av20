#ifndef DEVICECALIBRATION_H
#define DEVICECALIBRATION_H

#include <vector>
#include "definitions.h"

class DeviceCalibration
{
    TVGMode _tvgMode;
    int _tvgCurve;
    std::vector<uint8_t> _tvgPoints;
public:
    DeviceCalibration();
    DeviceCalibration(DeviceCalibration * original);
    DeviceCalibration *getSnapshot();
    // get/set
    int getTvgCurve() const;
    void setTvgCurve(int tvgCurve);
    TVGMode getTvgMode() const;
    void setTvgMode(const TVGMode &tvgMode);
    std::vector<uint8_t> getTvgPoints() const;
    void setTvgPoints(const std::vector<uint8_t> &tvgPoints);
};

#endif // DEVICECALIBRATION_H
