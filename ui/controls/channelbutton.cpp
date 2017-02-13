#include "channelbutton.h"
#include "ui_channelbutton.h"

ChannelButton::ChannelButton(QString name, uint8_t channel, QWidget *parent) :
    _name(name),
    _channel(channel),
    _state(false),
    QWidget(parent),
    ui(new Ui::ChannelButton)
{
    ui->setupUi(this);
    ui->channelButton->setText(name);
    _colorRed = 255;
    _colorGreen = 255;
    _colorBlue = 255;
    setActive(false);
    ui->channelButton->update();
}

ChannelButton::~ChannelButton()
{
    delete ui;
}

void ChannelButton::setActive(bool state)
{
    _state = state;
    if(state) {
        ui->channelButton->setStyleSheet("color: red; background-color: rgb("+QString::number(_colorRed)+","+QString::number(_colorGreen)+","+QString::number(_colorBlue)+")");
    } else {
        ui->channelButton->setStyleSheet("color: black; background-color: rgb("+QString::number(_colorRed)+","+QString::number(_colorGreen)+","+QString::number(_colorBlue)+")");
    }
    ui->channelButton->update();
}

void ChannelButton::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    _colorRed = red;
    _colorGreen = green;
    _colorBlue = blue;

    setActive(false);
}

void ChannelButton::on_channelButton_released()
{
    emit channelSelected(_channel);
    ui->channelButton->update();
}
