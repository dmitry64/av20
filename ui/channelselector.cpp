#include "channelselector.h"
#include "ui_channelselector.h"
#include <QDebug>

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

void ChannelSelector::init(ChannelsCalibration *snapshot)
{
    qDebug() << "Selector init!";
    Q_ASSERT(snapshot);
    for(size_t i=0; i<_channelButtons.size(); i++) {
        ChannelButton * button = _channelButtons.at(i);
        Q_ASSERT(button);
        ui->channelsLayout->removeWidget(button);
        QObject::disconnect(button,SIGNAL(channelSelected(uint8_t)),this,SLOT(onChannelSelected(uint8_t)));
        delete button;
    }
    int count = snapshot->getChannelsCount();
    _channelButtons.clear();
    for(int i=0; i<count; i++) {
        Channel * chan = snapshot->getChannel(i);
        ChannelButton * channelButton = new ChannelButton("Ch #" + QString::number(i),i);
        channelButton->setColor(chan->getColorRed(),chan->getColorGreen(), chan->getColorBlue());
        QObject::connect(channelButton,SIGNAL(channelSelected(uint8_t)),this,SLOT(onChannelSelected(uint8_t)));
        ui->channelsLayout->addWidget(channelButton);
        _channelButtons.push_back(channelButton);
    }
    _channelButtons[0]->setActive(true);

    update();
}

void ChannelSelector::setCore(Core *core)
{
    _core = core;
    update();
}

void ChannelSelector::onChannelSelected(uint8_t channel)
{
    for(int i=0;i<_channelButtons.size(); i++) {
        ChannelButton * button = _channelButtons.at(i);
        Q_ASSERT(button);
        button->setActive(i==channel);
    }
    emit channelChanged(channel);
}
