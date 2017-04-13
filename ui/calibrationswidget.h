#ifndef CALIBRATIONSWIDGET_H
#define CALIBRATIONSWIDGET_H

#include <QWidget>
#include "core.h"
#include "controls/calibrationbutton.h"
#include "keyboards/keyboard.h"

namespace Ui
{
class CalibrationsWidget;
}

class CalibrationsWidget : public QWidget
{
    Q_OBJECT

    Core * _core;
    std::vector<CalibrationButton *> _buttons;
    CalibrationIndex _selectedIndex;
    Keyboard * _keyboard;
public:
    explicit CalibrationsWidget(QWidget *parent = 0);
    void init(const ChannelsCalibration &calibration);
    void setCore(Core * core);
    ~CalibrationsWidget();

private slots:
    void onCalibrationSelected(CalibrationIndex index);
    void addCalibrationWithName(const QString &str);
    void on_newButton_released();
    void on_removeButton_released();
    void on_selectButton_2_released();

signals:
    void calibrationSelected();

private:
    Ui::CalibrationsWidget *ui;
    void clearButtons();
    void initButtons(const ChannelsCalibration& calibration, const CalibrationsInfoList& info);
    void changeEvent(QEvent *event);
};

#endif // CALIBRATIONSWIDGET_H
