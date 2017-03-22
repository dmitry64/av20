#include "system.h"

Filesystem *System::getFilesystem() const
{
    return _filesystem;
}

void System::shutdown()
{
    logEvent("System","Shutdown");
}

void System::reboot()
{
    logEvent("System","Reboot");
}

void System::onDeviceVersionReady(QString version)
{
    emit deviceVersionReady(version);
}

System::System()
{
    _filesystem = new Filesystem();
    _brightness = new BrightnessController();
    _temperature = new Temperature();
    _sound = new Sound();
    _battery = new BatteryController();
    _dateTime = new DateTimeController();
    connect(_temperature,SIGNAL(temperatureChanged(double)),this,SIGNAL(temperatureChanged(double)));
    connect(_battery,SIGNAL(batteryLevelChanged(int)),this,SIGNAL(batteryLevelChanged(int)));
    connect(_dateTime,SIGNAL(timeChanged(QDateTime)),this,SIGNAL(dateTimeChanged(QDateTime)));
}

void System::init()
{
    logEvent("System","System initializing");
    _filesystem->initFilesystem();
    _brightness->init();
    _temperature->init();
    _sound->init();
    _battery->init();
    _dateTime->init();
    logEvent("System","System initialized!");
}

QString System::getCurrentOperator()
{
    return "Ivanov A.A.";
}

QString System::getSoftwareVersion()
{
    return APP_VERSION;
}

QString System::getOSVersion()
{
    return "1.0.0";
}

void System::setDate(QDate date)
{
    _dateTime->setDate(date);
}

void System::setTime(QTime time)
{
    _dateTime->setTime(time);
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
    return _dateTime->getDate();
}

QTime System::getTime()
{
    return _dateTime->getTime();
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
