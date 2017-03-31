#include "statusbar.h"
#include "ui_statusbar.h"
#include "system/system.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
    ui->overheatButton->hide();
    ui->errorButton->hide();
    ui->connectionErrorButton->hide();
    ui->registrationButton->hide();
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::init()
{
    System * system = System::getInstance();
    Q_ASSERT(system);
    ui->operatorLabel->setText("Operator: " + system->getCurrentOperatorName());
    ui->timeLabel->setText(system->getTime().toString(Qt::DefaultLocaleShortDate));
    ui->dateLabel->setText(system->getDate().toString(Qt::DefaultLocaleShortDate));
    ui->batteryButton->setText(QString::number(system->getBatteryPercent()) + "%");
    ui->soundButton->setText(QString::number(system->getSoundVolume()) + "%");
    ui->tempButton->setText(QString::number(system->getTemperature()) + "\u2103");
    ui->brightnessButton->setText(QString::number(system->getBrightness()) + "%");
    ui->wifiButton->setText(QString::number(system->getWifiSignalLevel()) + "%");

    connect(system,SIGNAL(temperatureChanged(double)),this,SLOT(onTemperatureChanged(double)));
    connect(system,SIGNAL(brightnessChanged(int)),this,SLOT(onBrightnessChanged(int)));
    connect(system,SIGNAL(soundVolumeChanged(int)),this,SLOT(onSoundVolumeChanged(int)));
    connect(system,SIGNAL(batteryLevelChanged(int)),this,SLOT(onBatteryLevelChanged(int)));
    connect(system,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(onDateTimeChanged(QDateTime)));
    connect(system->getSettings(),SIGNAL(operatorNameChanged(QString)),this,SLOT(onOperatorChanged(QString)));
}

void StatusBar::onDeviceOverheatEnabled()
{
    ui->overheatButton->show();
}

void StatusBar::onDeviceOverheatDisabled()
{
    ui->overheatButton->hide();
}

void StatusBar::onDeviceErrorEnabled()
{
    ui->errorButton->show();
}

void StatusBar::onDeviceErrorDisabled()
{
    ui->errorButton->hide();
}

void StatusBar::onDeviceConnectionErrorEnabled()
{
    ui->connectionErrorButton->show();
}

void StatusBar::onDeviceConnectionErrorDisabled()
{
    ui->connectionErrorButton->hide();
}

void StatusBar::onOperatorChanged(QString name)
{
    ui->operatorLabel->setText("Operator: " +name);
}

void StatusBar::onRegistrationStatusChanged(bool status)
{
    if(status) {
        ui->registrationButton->show();
    }
    else {
        ui->registrationButton->hide();
    }
}

void StatusBar::onTemperatureChanged(double value)
{
    ui->tempButton->setText(QString::number(value) + "\u2103");
}

void StatusBar::onBatteryLevelChanged(int value)
{
    ui->batteryButton->setText(QString::number(value) + "%");
}

void StatusBar::onSoundVolumeChanged(int value)
{
    ui->soundButton->setText(QString::number(value) + "%");
}

void StatusBar::onBrightnessChanged(int value)
{
    ui->brightnessButton->setText(QString::number(value) + "%");
}

void StatusBar::onWiFiSignalLevelChanged(int value)
{
    ui->wifiButton->setText(QString::number(value) + "%");
}

void StatusBar::onDateTimeChanged(QDateTime time)
{
    ui->dateLabel->setText(time.date().toString(Qt::DefaultLocaleShortDate));
    ui->timeLabel->setText(time.time().toString(Qt::DefaultLocaleShortDate));
}
