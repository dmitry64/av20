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
    ui->channelButton->setStyleSheet("color: blue; background-color: yellow");
}

ChannelButton::~ChannelButton()
{
    delete ui;
}

void ChannelButton::setActive(bool state)
{
    _state = state;
    if(state) {
        ui->channelButton->setStyleSheet("color: blue; background-color: red");
    } else {
        ui->channelButton->setStyleSheet("color: blue; background-color: yellow");
    }
}

void ChannelButton::on_channelButton_released()
{
    emit channelSelected(_channel);
}
