#ifndef BRIGHTNESSCONTROLLER_H
#define BRIGHTNESSCONTROLLER_H


class BrightnessController
{
    int _currentBrightness;
public:
    void init();
    BrightnessController();
    int currentBrightness() const;
    void setCurrentBrightness(int currentBrightness);
};

#endif // BRIGHTNESSCONTROLLER_H
