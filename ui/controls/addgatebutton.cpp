#include "addgatebutton.h"
#include "ui_addgatebutton.h"

AddGateButton::AddGateButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddGateButton)
{
    ui->setupUi(this);
}

AddGateButton::~AddGateButton()
{
    delete ui;
}

void AddGateButton::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}

void AddGateButton::on_addButton_released()
{
    emit addGate();
}
