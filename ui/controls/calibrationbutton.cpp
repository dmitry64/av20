#include "calibrationbutton.h"
#include "ui_calibrationbutton.h"

CalibrationInfo CalibrationButton::info() const
{
    return _info;
}

CalibrationButton::CalibrationButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationButton)
{
    ui->setupUi(this);
    _active = false;
    _current = false;
}

CalibrationButton::~CalibrationButton()
{
    delete ui;
}

void CalibrationButton::setCalibrationInfo(const CalibrationInfo &info)
{
    _info = info;
    ui->idLabel->setText(QString::number(info._id));
    ui->calibrationButton->setText(info._name);
    _active = false;
}

void CalibrationButton::setActive(bool status)
{
    _active = status;
    if(!_active) {
        QPalette palette = ui->calibrationButton->palette();
        palette.setColor(QPalette::Button, QColor(100,100,100));
        ui->calibrationButton->setPalette(palette);
    }
    else {
        QPalette palette = ui->calibrationButton->palette();
        palette.setColor(QPalette::Button, QColor(108,189,64));
        ui->calibrationButton->setPalette(palette);
    }
}

void CalibrationButton::setCurrentCalibration(bool status)
{
    _current = status;
    if(!_current) {
        QPalette palette = ui->idLabel->palette();
        palette.setColor(QPalette::Background, QColor(100,100,100));
        ui->idLabel->setPalette(palette);
    }
    else {
        QPalette palette = ui->idLabel->palette();
        palette.setColor(QPalette::Background, QColor(255,189,64));
        ui->idLabel->setPalette(palette);
    }
}

void CalibrationButton::on_calibrationButton_released()
{
    emit calibrationSelected(_info._id);
}
