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

void ChannelSelector::init(const ChannelsCalibration & snapshot)
{
    qDebug() << "Selector init!";

    for(size_t i=0; i<_channelButtons.size(); i++) {
        ChannelButton * button = _channelButtons.at(i);
        Q_ASSERT(button);
        ui->channelsLayout->removeWidget(button);
        QObject::disconnect(button,SIGNAL(channelSelected(ChannelsInfo)),this,SLOT(onChannelSelected(ChannelsInfo)));
        delete button;
    }
    int count = snapshot.getChannelsCount();
    _channelButtons.clear();
    for(int i=0; i<count; i++) {
        const Channel & chan = snapshot.getChannel(i);
        const std::vector<DisplayChannel> & dispchans = chan.getDisplayChannels();
        for(size_t j=0; j<dispchans.size(); j++) {
            const DisplayChannel & dc = dispchans.at(j);
            ChannelsInfo info;
            info._channel = i;
            info._displayChannel = j;
            ChannelButton * channelButton = new ChannelButton(QString::number(dc.angle()),info);
            channelButton->setColor(chan.getColorRed(),chan.getColorGreen(), chan.getColorBlue());
            QObject::connect(channelButton,SIGNAL(channelSelected(ChannelsInfo)),this,SLOT(onChannelSelected(ChannelsInfo)));
            ui->channelsLayout->addWidget(channelButton);
            _channelButtons.push_back(channelButton);
        }
    }
    _channelButtons.at(0)->setActive(true);

    update();
}

void ChannelSelector::setCore(Core *core)
{
    _core = core;
    update();
}

void ChannelSelector::onChannelSelected(ChannelsInfo info)
{
    qDebug() << "Selector channel selected";
    for(size_t i=0; i<_channelButtons.size(); i++) {
        ChannelButton * button = _channelButtons.at(i);
        Q_ASSERT(button);
        button->setActive(button->info()._channel == info._channel && button->info()._displayChannel == info._displayChannel);
    }
    emit channelChanged(info);
}
