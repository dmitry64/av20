#include "schemeselectionbutton.h"
#include "ui_schemeselectionbutton.h"

SchemeSelectionButton::SchemeSelectionButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchemeSelectionButton)
{
    ui->setupUi(this);
}

SchemeSelectionButton::~SchemeSelectionButton()
{
    delete ui;
}

void SchemeSelectionButton::setText(QString text)
{
    ui->mainButton->setText(text);
}

void SchemeSelectionButton::setIndex(uint8_t index)
{
    _index = index;
}

void SchemeSelectionButton::on_mainButton_released()
{
    emit schemeSelected(_index);
}
