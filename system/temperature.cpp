#include "temperature.h"

void Temperature::init()
{
    _current = readTemperature();
    _updateTimer.setInterval(2000);
    connect(&_updateTimer,SIGNAL(timeout()),this,SLOT(updateValue()));
    _updateTimer.start();
}

double Temperature::getTemperature()
{
    return _current;
}

void Temperature::updateValue()
{
    _current = readTemperature();
    emit temperatureChanged(_current);
}

double Temperature::readTemperature()
{
    return 21.0 + (random() % 10) * 0.1;
}

Temperature::Temperature(QObject *parent) : QObject(parent), _current(0)
{

}
