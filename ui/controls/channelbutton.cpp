#include "channelbutton.h"
#include "ui_channelbutton.h"

ChannelButton::ChannelButton(QString name, ChannelID channel, DisplayChannelID disp, QWidget *parent) :
    QWidget(parent),
    _name(name),
    _channel(channel),
    _displayChannelId(disp),
    _state(false),
    ui(new Ui::ChannelButton)
{
    ui->setupUi(this);
    ui->channelButton->setText(name);
    _colorRed = 255;
    _colorGreen = 255;
    _colorBlue = 255;
    setActive(false);
    ui->channelMarkerButton->hide();
}

ChannelButton::~ChannelButton()
{
    delete ui;
}

void ChannelButton::setActive(bool state)
{
    _state = state;
    if(state) {
        ui->channelMarkerButton->show();
        ui->channelButton->setStyleSheet("color: green; background-color: rgb("+QString::number(_colorRed)+","+QString::number(_colorGreen)+","+QString::number(_colorBlue)+")");
        ui->colorWidget->setStyleSheet("background-color: rgb("+QString::number(_colorRed)+","+QString::number(_colorGreen)+","+QString::number(_colorBlue)+")");
    }
    else {
        ui->channelMarkerButton->hide();
        ui->channelButton->setStyleSheet("color: black; background-color: rgb("+QString::number(_colorRed)+","+QString::number(_colorGreen)+","+QString::number(_colorBlue)+")");
        ui->colorWidget->setStyleSheet("background-color: rgb("+QString::number(_colorRed)+","+QString::number(_colorGreen)+","+QString::number(_colorBlue)+")");
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
