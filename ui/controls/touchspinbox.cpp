#include "touchspinbox.h"
#include "ui_touchspinbox.h"

TouchSpinBox::TouchSpinBox(QString name, QWidget *parent) :
    QWidget(parent),
    _name(name),
    _value(0),
    ui(new Ui::TouchSpinBox)
{
    ui->setupUi(this);
    ui->nameLabel->setText(name);
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


void TouchSpinBox::on_leftButton_pressed()
{
    _value -= 1;
    ui->valueLabel->setText(QString::number(_value));
    emit valueChanged(_value);
}

void TouchSpinBox::on_rightButton_pressed()
{
    _value += 1;
    ui->valueLabel->setText(QString::number(_value));
    emit valueChanged(_value);
}
