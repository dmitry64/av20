#include "touchspinbox.h"
#include "ui_touchspinbox.h"

TouchSpinBox::TouchSpinBox(QWidget *parent) :
    QWidget(parent),
    _value(0),
    ui(new Ui::TouchSpinBox)
{
    ui->setupUi(this);
    ui->nameLabel->setText("");
    _timer.setInterval(100);
    connect(&_timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    _direction = false;
}

TouchSpinBox::~TouchSpinBox()
{
    delete ui;
}

void TouchSpinBox::setValue(double value)
{
    _value = value;
    ui->valueLabel->setText(QString::number(value));
}

void TouchSpinBox::setName(QString name)
{
    _name = name;
    ui->nameLabel->setText(name);
}

void TouchSpinBox::onTimer()
{
    if(_direction) {
        _value -= 1;
    } else {
        _value += 1;
    }
    ui->valueLabel->setText(QString::number(_value));
    emit valueChanged(_value);
}

void TouchSpinBox::on_leftButton_pressed()
{
    _value -= 1;
    ui->valueLabel->setText(QString::number(_value));
    _direction = true;
    _timer.start();

    emit valueChanged(_value);
}

void TouchSpinBox::on_rightButton_pressed()
{
    _value += 1;
    ui->valueLabel->setText(QString::number(_value));
    _timer.start();
    _direction = false;
    emit valueChanged(_value);
}

void TouchSpinBox::on_leftButton_released()
{
    _timer.stop();
}

void TouchSpinBox::on_rightButton_released()
{
    _timer.stop();
}
