#include "systemwidget.h"
#include "ui_systemwidget.h"

#include "system/system.h"

SystemWidget::SystemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemWidget)
{
    ui->setupUi(this);
    System * system = System::getInstance();
    ui->operatorLabel->setText(system->getCurrentOperator());
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

    ui->softwareVersionLabel->setText(system->getSoftwareVersion());
    ui->osVersionLabel->setText(system->getOSVersion());

    connect(ui->brightnessWidget,SIGNAL(valueChanged(double)),this,SLOT(onBrightnessChanged(double)));
    connect(ui->soundWidget,SIGNAL(valueChanged(double)),this,SLOT(onSoundVolumeChanged(double)));
    connect(system,SIGNAL(deviceVersionReady(QString)),this,SLOT(onUSMVersionChanged(QString)));
    connect(system,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(onDateTimeChanged(QDateTime)));
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

void SystemWidget::onBrightnessChanged(double value)
{
    System * system = System::getInstance();
    system->setBrightness(qRound(value));
}

void SystemWidget::onSoundVolumeChanged(double value)
{
    System * system = System::getInstance();
    system->setSoundVolume(qRound(value));
}

void SystemWidget::onUSMVersionChanged(QString string)
{
    ui->versionLabel->setText(string);
}

void SystemWidget::onDateTimeChanged(QDateTime time)
{
    ui->timeLabel->setText(time.time().toString(Qt::DefaultLocaleShortDate));
    ui->dateLabel->setText(time.date().toString(Qt::DefaultLocaleShortDate));
}
