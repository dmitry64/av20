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


void SystemWidget::on_shutdownButton_released()
{
    emit shutdown();
}

void SystemWidget::on_rebootButton_released()
{
    emit reboot();
}

void SystemWidget::on_pauseButton_released()
{
    emit pause();
}
