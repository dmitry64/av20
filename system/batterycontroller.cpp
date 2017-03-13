#include "batterycontroller.h"

int BatteryController::currentPercent() const
{
    return _currentPercent;
}

double BatteryController::readVoltage()
{
    return 100 - (random() % 10);
}

void BatteryController::updateValue()
{
    _currentPercent = readVoltage();
    emit batteryLevelChanged(_currentPercent);
}

BatteryController::BatteryController(QObject *parent) : QObject(parent), _currentPercent(0)
{

}

void BatteryController::init()
{
    _currentPercent = 100;
    _updateTimer.setInterval(5000);
    connect(&_updateTimer,SIGNAL(timeout()),this,SLOT(updateValue()));
    _updateTimer.start();
    logEvent("Battery","Ready");
}
