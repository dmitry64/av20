#ifndef BATTERYCONTROLLER_H
#define BATTERYCONTROLLER_H

#include <QObject>
#include <QTimer>

class BatteryController : public QObject
{
    Q_OBJECT
    int _currentPercent;
    QTimer _updateTimer;

    double readVoltage();
private slots:
    void updateValue();
public:
    explicit BatteryController(QObject *parent = 0);
    void init();
    int currentPercent() const;

signals:
    void batteryLevelChanged(int);
public slots:
};

#endif // BATTERYCONTROLLER_H
