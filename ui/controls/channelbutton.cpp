#include "channelbutton.h"
#include "ui_channelbutton.h"
#include <QDebug>

ChannelsInfo ChannelButton::info() const
{
    return _info;
}

void ChannelButton::setInfo(const ChannelsInfo &info)
{
    _info = info;
}

ChannelButton::ChannelButton(const QString &name, const ChannelsInfo &info, QWidget *parent) :
    QWidget(parent),
    _name(name),
    _state(false),
    ui(new Ui::ChannelButton)
{
    ui->setupUi(this);
    ui->channelButton->setText(name);
    _colorRed = 255;
    _colorGreen = 255;
    _colorBlue = 255;
    setActive(false);
    _info = info;
    _defaultPalette = ui->channelButton->palette();
    _activePalette = _defaultPalette;
    _activePalette.setColor(QPalette::Button,QColor(230,230,70));
    _activePalette.setColor(QPalette::ButtonText,Qt::black);
}

ChannelButton::~ChannelButton()
{
    delete ui;
}

void ChannelButton::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
}

void ChannelButton::setActive(bool state)
{
    _state = state;
    if(state) {
        ui->channelButton->setPalette(_activePalette);
    }
    else {
        ui->channelButton->setPalette(_defaultPalette);
    }
    ui->colorWidget->setStyleSheet("background-color: rgb("+QString::number(_colorRed)+","+QString::number(_colorGreen)+","+QString::number(_colorBlue)+")");
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
    ui->channelButton->update();
    emit channelSelected(_info);
}
