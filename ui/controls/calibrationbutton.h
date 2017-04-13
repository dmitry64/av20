#ifndef CALIBRATIONBUTTON_H
#define CALIBRATIONBUTTON_H

#include <QWidget>

#include "common/definitions.h"


namespace Ui
{
class CalibrationButton;
}

class CalibrationButton : public QWidget
{
    Q_OBJECT

    CalibrationInfo _info;
    bool _active;
    bool _current;
public:
    explicit CalibrationButton(QWidget *parent = 0);
    ~CalibrationButton();
    void setCalibrationInfo(const CalibrationInfo & info);
    void setActive(bool status);
    void setCurrentCalibration(bool status);
    CalibrationInfo info() const;

signals:
    void calibrationSelected(CalibrationIndex index);

private slots:
    void on_calibrationButton_released();

private:
    Ui::CalibrationButton *ui;
    void changeEvent(QEvent *event);
};

#endif // CALIBRATIONBUTTON_H
