#ifndef BRIGHTNESSCONTROLLER_H
#define BRIGHTNESSCONTROLLER_H

#include "common/commonfunctions.h"
#include "settings.h"

class BrightnessController
{
    int _currentBrightness;
public:
    void init(Settings * settings);
    BrightnessController();
    int currentBrightness() const;
    void setCurrentBrightness(int currentBrightness);
};

#endif // BRIGHTNESSCONTROLLER_H
