#include "touchspinbox.h"
#include "ui_touchspinbox.h"

TouchSpinBox::TouchSpinBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TouchSpinBox)
{
    ui->setupUi(this);
}

TouchSpinBox::~TouchSpinBox()
{
    delete ui;
}
