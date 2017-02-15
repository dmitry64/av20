#include "touchspinbox.h"
#include "ui_touchspinbox.h"

void TouchSpinBox::inc()
{
    if(_value < _max) {
        _value += _step;
    }
}

void TouchSpinBox::dec()
{
    if(_value > _min) {
        _value -= _step;
    }
}

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
    _min = 0;
    _max = 255;
    _step = 1;
    _suffix = QString("");
}

TouchSpinBox::~TouchSpinBox()
{
    delete ui;
}

void TouchSpinBox::setValue(double value)
{
    _value = value;
    ui->valueLabel->setText(QString::number(value) + " " + _suffix);
    update();
}

void TouchSpinBox::setName(QString name)
{
    _name = name;
    ui->nameLabel->setText(name);
    update();
}

void TouchSpinBox::setMax(double max)
{
    _max = max;
}

void TouchSpinBox::setMin(double min)
{
    _min = min;
}

void TouchSpinBox::setStep(double step)
{
    _step = step;
}

void TouchSpinBox::setSuffix(QString suf)
{
    _suffix = suf;
    update();
}

void TouchSpinBox::onTimer()
{
    if(_direction) {
        dec();
    } else {
        inc();
    }
    ui->valueLabel->setText(QString::number(_value) + " " + _suffix);
    update();
    emit valueChanged(_value);
}

void TouchSpinBox::on_leftButton_pressed()
{
    dec();
    ui->valueLabel->setText(QString::number(_value) + " " + _suffix);
    _direction = true;
    _timer.start();
    update();
    emit valueChanged(_value);
}

void TouchSpinBox::on_rightButton_pressed()
{
    inc();
    ui->valueLabel->setText(QString::number(_value) + " " + _suffix);
    _timer.start();
    _direction = false;
    update();
    emit valueChanged(_value);
}

void TouchSpinBox::on_leftButton_released()
{
    _timer.stop();
    update();
}

void TouchSpinBox::on_rightButton_released()
{
    _timer.stop();
    update();
}
