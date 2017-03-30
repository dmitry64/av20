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
}

RegistrationWidget::~RegistrationWidget()
{
    delete ui;
}
