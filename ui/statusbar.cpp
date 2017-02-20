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
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::init()
{
    System * system = System::getInstance();
    Q_ASSERT(system);
    ui->timeLabel->setText(system->getTime().toString(Qt::DefaultLocaleShortDate));
    ui->dateLabel->setText(system->getDate().toString(Qt::DefaultLocaleShortDate));
    ui->batteryButton->setText(QString::number(system->getBatteryPercent()) + "%");
    ui->soundButton->setText(QString::number(system->getSoundVolume()) + "%");
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
