#ifndef DATETIMECONTROLLER_H
#define DATETIMECONTROLLER_H

#include "device/commonfunctions.h"
#include <QObject>

#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimer>

class DateTimeController : public QObject
{
    Q_OBJECT
    QTimer _timer;
    QDateTime _lastTime;
public:
    explicit DateTimeController(QObject *parent = 0);

    void init();
    void setDate(QDate date);
    void setTime(QTime time);
    QDate getDate();
    QTime getTime();

signals:
    void timeChanged(QDateTime dateTime);
private slots:
    void update();
};

#endif // DATETIMECONTROLLER_H
