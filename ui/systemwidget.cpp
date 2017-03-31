#include "systemwidget.h"
#include "ui_systemwidget.h"

#include "system/system.h"

SystemWidget::SystemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemWidget)
{
    ui->setupUi(this);
    System * system = System::getInstance();
    ui->operatorLabel->setText(system->getCurrentOperatorName());

    ui->timeLabel->setText(system->getTime().toString(Qt::DefaultLocaleShortDate));
    ui->dateLabel->setText(system->getDate().toString(Qt::DefaultLocaleShortDate));

    ui->softwareVersionLabel->setText(system->getSoftwareVersion());
    ui->osVersionLabel->setText(system->getOSVersion());


    connect(system,SIGNAL(deviceVersionReady(QString)),this,SLOT(onUSMVersionChanged(QString)));
    connect(system,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(onDateTimeChanged(QDateTime)));
    connect(system->getSettings(),SIGNAL(operatorNameChanged(QString)),this,SLOT(onOperatorChanged(QString)));
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

void SystemWidget::onUSMVersionChanged(QString string)
{
    ui->versionLabel->setText(string);
}

void SystemWidget::onDateTimeChanged(QDateTime time)
{
    ui->timeLabel->setText(time.time().toString(Qt::DefaultLocaleShortDate));
    ui->dateLabel->setText(time.date().toString(Qt::DefaultLocaleShortDate));
}

void SystemWidget::onOperatorChanged(QString name)
{
    ui->operatorLabel->setText(name);
}
