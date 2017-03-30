#include "touchspinbox.h"
#include "ui_touchspinbox.h"

double TouchSpinBox::value() const
{
    return _value;
}

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

void TouchSpinBox::sync()
{
    ui->valueLabel->setText(QString::number(_value) + " " + _suffix);
    ui->leftButton->setEnabled(_value > _min);
    ui->rightButton->setEnabled(_value < _max);
    update();
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
    _value = 0;
    _prev = 0;
    _suffix = QString("");
}

TouchSpinBox::~TouchSpinBox()
{
    delete ui;
}

void TouchSpinBox::setValue(double value)
{
    _value = value;
    _prev = value;
    sync();
}

void TouchSpinBox::setName(QString name)
{
    _name = name;
    ui->nameLabel->setText(name);
    sync();
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
    sync();
}

void TouchSpinBox::onTimer()
{
    _prev = _value;
    if(_direction) {
        dec();
    }
    else {
        inc();
    }
    if(_prev!=_value) {
        sync();
        emit valueChanged(_value);
    }
}

void TouchSpinBox::on_leftButton_pressed()
{
    dec();
    sync();
    _direction = true;
    _timer.start();
    emit valueChanged(_value);
}

void TouchSpinBox::on_rightButton_pressed()
{
    inc();
    sync();
    _timer.start();
    _direction = false;
    emit valueChanged(_value);
}

void TouchSpinBox::on_leftButton_released()
{
    _timer.stop();
    sync();
}

void TouchSpinBox::on_rightButton_released()
{
    _timer.stop();
    sync();
}
