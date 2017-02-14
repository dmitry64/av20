#include "systemwidget.h"
#include "ui_systemwidget.h"

SystemWidget::SystemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemWidget)
{
    ui->setupUi(this);
}

SystemWidget::~SystemWidget()
{
    delete ui;
}
