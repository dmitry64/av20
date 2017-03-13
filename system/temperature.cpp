#include "temperature.h"

void Temperature::init()
{
    _current = 21.0;
    _current = readTemperature();
    _updateTimer.setInterval(6000);
    connect(&_updateTimer,SIGNAL(timeout()),this,SLOT(updateValue()));
    _updateTimer.start();
    logEvent("Temperature","Ready");
}

double Temperature::getTemperature()
{
    return _current;
}

void Temperature::updateValue()
{
    double temp = readTemperature();
    if(temp!=_current) {
        logEvent("Temperature","Temperature changed to " + QString::number(temp));
        _current = temp;
        emit temperatureChanged(_current);
    }
}

double Temperature::readTemperature()
{
    return _current + (random() % 3 - 1) * 0.1;
}

Temperature::Temperature(QObject *parent) : QObject(parent), _current(0)
{

}
