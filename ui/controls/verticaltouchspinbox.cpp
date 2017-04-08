#include "verticaltouchspinbox.h"
#include "ui_verticaltouchspinbox.h"

VerticalTouchSpinBox::VerticalTouchSpinBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VerticalTouchSpinBox)
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

VerticalTouchSpinBox::~VerticalTouchSpinBox()
{
    delete ui;
}

int VerticalTouchSpinBox::index() const
{
    return _index;
}

void VerticalTouchSpinBox::setIndex(int index)
{
    _index = index;
}

void VerticalTouchSpinBox::inc()
{
    if(_value < _max) {
        _value += _step;
    }
}

void VerticalTouchSpinBox::dec()
{
    if(_value > _min) {
        _value -= _step;
    }
}

void VerticalTouchSpinBox::sync()
{
    ui->valueLabel->setText(QString::number(_value) + " " + _suffix);
    ui->downButton->setEnabled(_value > _min);
    ui->upButton->setEnabled(_value < _max);
    update();
}

void VerticalTouchSpinBox::setValue(double value)
{
    _value = value;
    _prev = value;
    sync();
}

void VerticalTouchSpinBox::setName(const QString &name)
{
    _name = name;
    ui->nameLabel->setText(name);
    sync();
}

void VerticalTouchSpinBox::setMax(double max)
{
    _max = max;
}

void VerticalTouchSpinBox::setMin(double min)
{
    _min = min;
}

void VerticalTouchSpinBox::setStep(double step)
{
    _step = step;
}

void VerticalTouchSpinBox::setSuffix(const QString & suf)
{
    _suffix = suf;
    sync();
}

void VerticalTouchSpinBox::onTimer()
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

void VerticalTouchSpinBox::on_upButton_pressed()
{
    inc();
    sync();
    _timer.start();
    _direction = false;
    emit valueChanged(_value);
}

void VerticalTouchSpinBox::on_upButton_released()
{
    _timer.stop();
    sync();
}

void VerticalTouchSpinBox::on_downButton_pressed()
{
    dec();
    sync();
    _direction = true;
    _timer.start();
    emit valueChanged(_value);
}

void VerticalTouchSpinBox::on_downButton_released()
{
    _timer.stop();
    sync();
}
