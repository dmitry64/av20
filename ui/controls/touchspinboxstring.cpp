#include "touchspinboxstring.h"
#include "ui_touchspinboxstring.h"

void TouchSpinBoxString::next()
{
    if(_current<_values.size()-1) {
        _current++;
    }
    emit valueChanged(_values.at(_current));
    emit indexChanged(_current);
    sync();
}

void TouchSpinBoxString::prev()
{
    if(_current>0) {
        _current--;
    }
    emit valueChanged(_values.at(_current));
    emit indexChanged(_current);
    sync();
}

void TouchSpinBoxString::sync()
{
    ui->valueLabel->setText(_values.at(_current));
    ui->leftButton->setEnabled(_current>0);
    ui->rightButton->setEnabled(_current<_values.size()-1);
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

void TouchSpinBoxString::setValues(const std::vector<QString> &values)
{
    _values = values;
    ui->valueLabel->setText(values.at(0));
    _current = 0;
    update();
}

void TouchSpinBoxString::setName(const QString &name)
{
    _name = name;
    sync();
}

void TouchSpinBoxString::setIndex(size_t index)
{
    _current = index;
    sync();
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
