#include "channelselector.h"
#include "ui_channelselector.h"


ChannelSelector::ChannelSelector(QWidget *parent) :
    QWidget(parent),
    _core(0),
    ui(new Ui::ChannelSelector)
{
    ui->setupUi(this);
}

ChannelSelector::~ChannelSelector()
{
    delete ui;
}

void ChannelSelector::init(DeviceCalibration *snapshot)
{
    int count = snapshot->getChannelsCount();
    if(_channelButtons.size() == 0) {
        for(int i=0; i<count; i++) {
            ChannelButton * channelButton = new ChannelButton("Ch #" + QString::number(i),i);
            QObject::connect(channelButton,SIGNAL(channelSelected(uint8_t)),this,SLOT(onChannelSelected(uint8_t)));
            ui->channelsLayout->addWidget(channelButton);
            _channelButtons.push_back(channelButton);
        }
        _channelButtons[0]->setActive(true);
    }
}

void ChannelSelector::setCore(Core *core)
{
    _core = core;
}

void ChannelSelector::onChannelSelected(uint8_t channel)
{
    for(int i=0;i<_channelButtons.size(); i++) {
        _channelButtons[i]->setActive(i==channel);
    }
    emit channelChanged(channel);
}
