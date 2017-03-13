#include "datetimecontroller.h"

DateTimeController::DateTimeController(QObject *parent) : QObject(parent)
{

}

void DateTimeController::init()
{
    _lastTime = QDateTime::currentDateTime();
    _timer.setInterval(1000);
    connect(&_timer,SIGNAL(timeout()),this,SLOT(update()));
    _timer.start();
    logEvent("DateTime","Ready");
}

void DateTimeController::setDate(QDate date)
{
    logEvent("DateTime","Set date");
}

void DateTimeController::setTime(QTime time)
{
    logEvent("DateTime","Set time");
}

QDate DateTimeController::getDate()
{
    return QDate::currentDate();
}

QTime DateTimeController::getTime()
{
    return QTime::currentTime();
}

void DateTimeController::update()
{
    QDateTime temp = QDateTime::currentDateTime();
    if(_lastTime.time().minute()!=temp.time().minute()) {
        _lastTime = temp;
        emit timeChanged(_lastTime);
    }
}
