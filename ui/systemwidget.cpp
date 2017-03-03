#include "systemwidget.h"
#include "ui_systemwidget.h"

#include "system/system.h"

SystemWidget::SystemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemWidget)
{
    ui->setupUi(this);
    System * system = System::getInstance();
    ui->soundWidget->setName("Volume");
    ui->soundWidget->setSuffix("%");
    ui->soundWidget->setMax(100);
    ui->soundWidget->setValue(system->getSoundVolume());

    ui->brightnessWidget->setName("Brightness");
    ui->brightnessWidget->setSuffix("%");
    ui->brightnessWidget->setMax(100);
    ui->brightnessWidget->setValue(system->getBrightness());

    ui->timeLabel->setText(system->getTime().toString(Qt::DefaultLocaleShortDate));
    ui->dateLabel->setText(system->getDate().toString(Qt::DefaultLocaleShortDate));
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
