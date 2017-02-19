#include "calibrationswidget.h"
#include "ui_calibrationswidget.h"

CalibrationsWidget::CalibrationsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalibrationsWidget)
{
    ui->setupUi(this);
}

CalibrationsWidget::~CalibrationsWidget()
{
    delete ui;
}
