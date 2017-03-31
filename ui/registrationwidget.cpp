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
        ui->startButton->setText("Stop registration");
        QString filePath = System::getInstance()->getFilesystem()->getDataPath() + "/" + System::getInstance()->getTimestamp()+".dat";
        _core->startRegistration(filePath);
    }
    else {
        ui->startButton->setText("Start registration");
        _core->stopRegistration();
    }
}
