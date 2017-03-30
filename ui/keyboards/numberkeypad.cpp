#include "numberkeypad.h"
#include "ui_numberkeypad.h"

NumberKeypad::NumberKeypad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumberKeypad)
{
    ui->setupUi(this);
}

NumberKeypad::~NumberKeypad()
{
    delete ui;
}

void NumberKeypad::on_button1_released()
{
    emit textTyped("1");
}

void NumberKeypad::on_button2_released()
{
    emit textTyped("2");
}

void NumberKeypad::on_button3_released()
{
    emit textTyped("3");
}

void NumberKeypad::on_button4_released()
{
    emit textTyped("4");
}

void NumberKeypad::on_button5_released()
{
    emit textTyped("5");
}

void NumberKeypad::on_button6_released()
{
    emit textTyped("6");
}

void NumberKeypad::on_button7_released()
{
    emit textTyped("7");
}

void NumberKeypad::on_button8_released()
{
    emit textTyped("8");
}

void NumberKeypad::on_button9_released()
{
    emit textTyped("9");
}

void NumberKeypad::on_button0_released()
{
    emit textTyped("0");
}

void NumberKeypad::on_sq1_released()
{
    emit textTyped("[");
}

void NumberKeypad::on_fig1_released()
{
    emit textTyped("{");
}

void NumberKeypad::on_mark_released()
{
    emit textTyped("!");
}

void NumberKeypad::on_at_released()
{
    emit textTyped("@");
}

void NumberKeypad::on_diez_released()
{
    emit textTyped("#");
}

void NumberKeypad::on_percent_released()
{
    emit textTyped("%");
}

void NumberKeypad::on_upper_released()
{
    emit textTyped("^");
}

void NumberKeypad::on_andButton_released()
{
    emit textTyped("&");
}

void NumberKeypad::on_mult_released()
{
    emit textTyped("*");
}

void NumberKeypad::on_par1_released()
{
    emit textTyped("(");
}

void NumberKeypad::on_par2_released()
{
    emit textTyped(")");
}

void NumberKeypad::on_plus_released()
{
    emit textTyped("+");
}

void NumberKeypad::on_sq2_released()
{
    emit textTyped("]");
}

void NumberKeypad::on_fig2_released()
{
    emit textTyped("}");
}
