#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QDate>
#include <QTime>

namespace Ui
{
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = 0);
    ~StatusBar();
    void init();
public slots:
    void onDeviceOverheatEnabled();
    void onDeviceOverheatDisabled();
    void onDeviceErrorEnabled();
    void onDeviceErrorDisabled();
    void onDeviceConnectionErrorEnabled();
    void onDeviceConnectionErrorDisabled();
    void onOperatorChanged(QString name);

    void onTemperatureChanged(double value);
    void onBatteryLevelChanged(int value);
    void onSoundVolumeChanged(int value);
    void onBrightnessChanged(int value);
    void onWiFiSignalLevelChanged(int value);

    void onDateTimeChanged(QDateTime time);
private:
    Ui::StatusBar *ui;
};

#endif // STATUSBAR_H
