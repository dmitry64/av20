#include "brightnesscontroller.h"

int BrightnessController::currentBrightness() const
{
    return _currentBrightness;
}

void BrightnessController::setCurrentBrightness(int currentBrightness)
{
    logEvent("Brightness","Brightness changed to "+QString::number(currentBrightness) + "%");
    _currentBrightness = currentBrightness;
}

void BrightnessController::init()
{
    _currentBrightness = 100;
    logEvent("Brightness","Ready");
}

BrightnessController::BrightnessController() : _currentBrightness(0)
{
}
