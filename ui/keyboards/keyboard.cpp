#include "keyboard.h"
#include "ui_keyboard.h"

Keyboard::Keyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);
    connect(ui->numberKeypadWidget,SIGNAL(textTyped(QString)),this,SLOT(onSymbolsSelected(QString)));
    connect(ui->englishKeyboard,SIGNAL(textTyped(QString)),this,SLOT(onSymbolsSelected(QString)));
    _isShiftMode = false;
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::on_enterButton_released()
{
    this->hide();
    emit textReady(ui->textField->text());
    this->deleteLater();
}

void Keyboard::on_cancelButton_released()
{
    ui->textField->setText("");
    this->hide();
    this->deleteLater();
}

void Keyboard::onSymbolsSelected(QString str)
{
    if(_isShiftMode) {
        ui->textField->setText(ui->textField->text()+str.toUpper());
    }
    else {
        ui->textField->setText(ui->textField->text()+str);
    }
}

void Keyboard::on_clearButton_released()
{
    ui->textField->setText("");
}

void Keyboard::on_shiftButton_released()
{
    _isShiftMode = !_isShiftMode;
    if(_isShiftMode) {
        ui->shiftButton->setText("Active");
    }
    else {
        ui->shiftButton->setText("");
    }
}
