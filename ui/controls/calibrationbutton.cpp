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
    _status = false;
}

CalibrationButton::~CalibrationButton()
{
    delete ui;
}

void CalibrationButton::setCalibrationInfo(CalibrationInfo info)
{
    _info = info;
    ui->idLabel->setText(QString::number(info._id));
    ui->calibrationButton->setText(info._name);
    _status = false;
}

void CalibrationButton::setActive(bool status)
{
    _status = status;
    if(!_status) {
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

void CalibrationButton::on_calibrationButton_released()
{
    emit calibrationSelected(_info._id);
}
