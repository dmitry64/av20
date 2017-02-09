#include "channelselector.h"
#include "ui_channelselector.h"
#include "ui/controls/channelbutton.h"

ChannelSelector::ChannelSelector(QWidget *parent) :
    QWidget(parent),
    _core(0),
    ui(new Ui::ChannelSelector)
{
    ui->setupUi(this);
    for(int i=0; i<8; i++) {
        ChannelButton * channelButton = new ChannelButton("Ch #" + QString::number(i),i);
        QObject::connect(channelButton,SIGNAL(channelSelected(uint8_t)),this,SLOT(onChannelSelected(uint8_t)));
        ui->channelsLayout->addWidget(channelButton);
    }
}

ChannelSelector::~ChannelSelector()
{
    delete ui;
}

void ChannelSelector::setCore(Core *core)
{
    _core = core;
}

void ChannelSelector::onChannelSelected(uint8_t channel)
{
    if(_core != 0) {
        _core->setSingleChannel(channel);
    }
}
