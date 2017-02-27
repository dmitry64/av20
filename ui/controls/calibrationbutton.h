#ifndef CALIBRATIONBUTTON_H
#define CALIBRATIONBUTTON_H

#include <QWidget>

#include "device/definitions.h"


namespace Ui {
class CalibrationButton;
}

class CalibrationButton : public QWidget
{
    Q_OBJECT

    CalibrationInfo _info;
    bool _status;
public:
    explicit CalibrationButton(QWidget *parent = 0);
    ~CalibrationButton();
    void setCalibrationInfo(CalibrationInfo info);
    void setActive(bool status);
signals:
    void calibrationSelected(CalibrationIndex index);

private slots:
    void on_calibrationButton_released();

private:
    Ui::CalibrationButton *ui;
};

#endif // CALIBRATIONBUTTON_H
