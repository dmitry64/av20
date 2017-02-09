#include "devicecalibration.h"

int DeviceCalibration::getTvgCurve() const
{
    return _tvgCurve;
}

void DeviceCalibration::setTvgCurve(int tvgCurve)
{
    _tvgCurve = tvgCurve;
}

TVGMode DeviceCalibration::getTvgMode() const
{
    return _tvgMode;
}

void DeviceCalibration::setTvgMode(const TVGMode &tvgMode)
{
    _tvgMode = tvgMode;
}

std::vector<uint8_t> DeviceCalibration::getTvgPoints() const
{
    return _tvgPoints;
}

void DeviceCalibration::setTvgPoints(const std::vector<uint8_t> &tvgPoints)
{
    _tvgPoints = tvgPoints;
}

DeviceCalibration::DeviceCalibration() :
    _tvgMode(TVGMode::CurveMode),
    _tvgCurve(0)
{

}

DeviceCalibration::DeviceCalibration(DeviceCalibration *original)
{
    _tvgMode = original->getTvgMode();
    _tvgCurve = original->getTvgCurve();
    _tvgPoints = original->getTvgPoints();
}

DeviceCalibration * DeviceCalibration::getSnapshot()
{
    return new DeviceCalibration(this);
}
