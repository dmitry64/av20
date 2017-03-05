#include "brightnesscontroller.h"

int BrightnessController::currentBrightness() const
{
    return _currentBrightness;
}

void BrightnessController::setCurrentBrightness(int currentBrightness)
{
    _currentBrightness = currentBrightness;
}

void BrightnessController::init()
{
    _currentBrightness = 100;
}

BrightnessController::BrightnessController() : _currentBrightness(0)
{
}
