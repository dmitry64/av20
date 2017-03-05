#include "system.h"

Filesystem *System::getFilesystem() const
{
    return _filesystem;
}

System::System()
{
    _filesystem = new Filesystem();
    _brightness = new BrightnessController();
    _temperature = new Temperature();
    _sound = new Sound();
    _battery = new BatteryController();
    connect(_temperature,SIGNAL(temperatureChanged(double)),this,SIGNAL(temperatureChanged(double)));
    connect(_battery,SIGNAL(batteryLevelChanged(int)),this,SIGNAL(batteryLevelChanged(int)));
}

void System::init()
{
    _filesystem->initFilesystem();
    _brightness->init();
    _temperature->init();
    _sound->init();
    _battery->init();
}

void System::setDate(QDate date)
{

}

void System::setTime(QTime time)
{

}

void System::setBrightness(int percent)
{
    _brightness->setCurrentBrightness(percent);
    emit brightnessChanged(percent);
}

void System::setSoundVolume(int percent)
{
    _sound->setVolume(percent);
    emit soundVolumeChanged(percent);
}

QDate System::getDate()
{
    return QDate::currentDate();
}

QTime System::getTime()
{
    return QTime::currentTime();
}

int System::getBrightness()
{
    return _brightness->currentBrightness();
}

double System::getTemperature()
{
    return _temperature->getTemperature();
}

int System::getSoundVolume()
{
    return _sound->volume();
}

int System::getBatteryPercent()
{
    return _battery->currentPercent();
}

int System::getWifiSignalLevel()
{
    return 78;
}
