#ifndef CALIBRATIONSWIDGET_H
#define CALIBRATIONSWIDGET_H

#include <QWidget>
#include "core.h"
#include "controls/calibrationbutton.h"


namespace Ui {
class CalibrationsWidget;
}

class CalibrationsWidget : public QWidget
{
    Q_OBJECT

    Core * _core;
    std::vector<CalibrationButton *> _buttons;
    CalibrationIndex _selectedIndex;
public:
    explicit CalibrationsWidget(QWidget *parent = 0);
    void init(ChannelsCalibration *calibration);
    void setCore(Core * core);
    ~CalibrationsWidget();



private slots:
    void onCalibrationSelected(CalibrationIndex index);
    void on_newButton_released();
    void on_removeButton_released();
    void on_selectButton_2_released();

signals:
    void calibrationSelected();

private:
    Ui::CalibrationsWidget *ui;
};

#endif // CALIBRATIONSWIDGET_H
