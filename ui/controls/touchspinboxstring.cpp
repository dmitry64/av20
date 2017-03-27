#include "touchspinboxstring.h"
#include "ui_touchspinboxstring.h"

void TouchSpinBoxString::next()
{
    if(_current<_values.size()-1) {
        _current++;
    }
    emit valueChanged(_values.at(_current));
    updateValue();
}

void TouchSpinBoxString::prev()
{
    if(_current>0) {
        _current--;
    }
    emit valueChanged(_values.at(_current));
    updateValue();
}

void TouchSpinBoxString::updateValue()
{
    ui->valueLabel->setText(_values.at(_current));
    update();
}

TouchSpinBoxString::TouchSpinBoxString(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TouchSpinBoxString)
{
    ui->setupUi(this);
    _current = 0;
}

TouchSpinBoxString::~TouchSpinBoxString()
{
    delete ui;
}

void TouchSpinBoxString::setValues(std::vector<QString> values)
{
    _values = values;
    ui->valueLabel->setText(values.at(0));
    _current = 0;
    update();
}

void TouchSpinBoxString::setName(QString name)
{
    _name = name;
    ui->nameLabel->setText(name);
    update();
}

void TouchSpinBoxString::on_leftButton_pressed()
{
    prev();
}

void TouchSpinBoxString::on_rightButton_pressed()
{
    next();
}

void TouchSpinBoxString::on_leftButton_released()
{

}

void TouchSpinBoxString::on_rightButton_released()
{

}
