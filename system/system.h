#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QTime>
#include <QDate>

#include "filesystem.h"
#include "brightnesscontroller.h"
#include "temperature.h"
#include "sound.h"
#include "batterycontroller.h"

class System : public QObject
{
    Q_OBJECT

    Filesystem * _filesystem;
    BrightnessController * _brightness;
    Temperature * _temperature;
    Sound * _sound;
    BatteryController * _battery;
private:
    System();
    System( const System &);
    System & operator= (System &);

public:
    static System * getInstance()
    {
        static System * _instance;
        if(_instance == 0) {
            _instance = new System();
        }
        return _instance;
    }

    void init();
    void setDate(QDate date);
    void setTime(QTime time);
    void setBrightness(int percent);
    void setSoundVolume(int percent);

    QDate getDate();
    QTime getTime();
    int getBrightness();
    double getTemperature();
    int getSoundVolume();
    int getBatteryPercent();
    int getWifiSignalLevel();

    Filesystem *getFilesystem() const;

signals:
    void dateChanged(QDate date);
    void timeChanged(QTime date);
    void temperatureChanged(double);
    void brightnessChanged(int);
    void soundVolumeChanged(int);
    void batteryLevelChanged(int percent);
};

#endif // SYSTEM_H
