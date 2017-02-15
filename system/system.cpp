#include "system.h"

Filesystem *System::getFilesystem() const
{
    return _filesystem;
}

System::System()
{
    _filesystem = new Filesystem();
}

void System::init()
{
    _filesystem->initFilesystem();
}

void System::setDate(QDate date)
{

}

void System::setTime(QTime time)
{

}

void System::setBrightness(int percent)
{

}

void System::setSoundVolume(int percent)
{

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
    return 76;
}

int System::getSoundVolume()
{
    return 82;
}

int System::getBatteryPercent()
{
    return 98;
}
