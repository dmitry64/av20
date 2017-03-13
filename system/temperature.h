#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <QObject>
#include <QTimer>

#include "device/commonfunctions.h"

class Temperature : public QObject
{
    Q_OBJECT

    double _current;
    QTimer _updateTimer;

    double readTemperature();
private slots:
    void updateValue();
signals:
    void temperatureChanged(double);
public:
    void init();
    double getTemperature();

    explicit Temperature(QObject *parent = 0);


};

#endif // TEMPERATURE_H
