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

void BrightnessController::init(Settings *settings)
{
    _currentBrightness = settings->getSystemScreenBrightness();
    logEvent("Brightness","Ready");
}

BrightnessController::BrightnessController() : _currentBrightness(0)
{
}
