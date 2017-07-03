#include "registrationwidget.h"
#include "ui_registrationwidget.h"

#include "system/system.h"

RegistrationWidget::RegistrationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWidget)
{
    ui->setupUi(this);
    System * system = System::getInstance();
    ui->dateLabel->setText(system->getDate().toString(Qt::DefaultLocaleShortDate));
    ui->operatorLabel->setText(system->getCurrentOperatorName());
    _registrationEnabled = false;
}

void RegistrationWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        System * system = System::getInstance();
        ui->dateLabel->setText(system->getDate().toString(Qt::DefaultLocaleShortDate));
        ui->operatorLabel->setText(system->getCurrentOperatorName());
    }
    QWidget::changeEvent(event);
}

void RegistrationWidget::setCore(Core *core)
{
    _core = core;
}

void RegistrationWidget::init()
{

}

RegistrationWidget::~RegistrationWidget()
{
    delete ui;
}

void RegistrationWidget::on_startButton_released()
{
    _registrationEnabled = !_registrationEnabled;
    if(_registrationEnabled) {
        ui->startButton->setText(tr("Stop registration"));
        QString filePath = System::getInstance()->getFilesystem()->getDataPath() + "/" + System::getInstance()->getTimestamp()+".dat";
        _core->startRegistration(filePath);
    }
    else {
        ui->startButton->setText(tr("Start registration"));
        _core->stopRegistration();
    }
}
