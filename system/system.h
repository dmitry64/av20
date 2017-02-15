#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QTime>
#include <QDate>

#include "filesystem.h"

class System : public QObject
{
    Q_OBJECT

    Filesystem * _filesystem;
private:
    System();
    System( const System &);
    System & operator= (System &);

public:
    static System * getInstance() {
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
    int getSoundVolume();
    int getBatteryPercent();

    Filesystem *getFilesystem() const;

signals:
    void dateTimeChanged(QDateTime time);
    void batteryLevelChanged(int percent);
};

#endif // SYSTEM_H
