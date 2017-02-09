#include "channelbutton.h"
#include "ui_channelbutton.h"

ChannelButton::ChannelButton(QString name, uint8_t channel, QWidget *parent) :
    _name(name),
    _channel(channel),
    QWidget(parent),
    ui(new Ui::ChannelButton)
{
    ui->setupUi(this);
    ui->channelButton->setText(name);
}

ChannelButton::~ChannelButton()
{
    delete ui;
}

void ChannelButton::on_channelButton_released()
{
    emit channelSelected(_channel);
}
