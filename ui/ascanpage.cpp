#include "ascanpage.h"
#include "ui_ascanpage.h"
#include <QDebug>

void AScanPage::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    switchToSelectedChannel();
}

AScanPage::AScanPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanPage)
{
    ui->setupUi(this);
    connect(ui->channelSelector,SIGNAL(channelChanged(ChannelsInfo)),this,SLOT(setChannel(ChannelsInfo)));
    ui->aScanInfoWidget->hide();
}

AScanPage::~AScanPage()
{
    delete ui;
}

void AScanPage::reset()
{
    ui->ascanWidget->reset();
    ui->bscanWidget->reset();
}

void AScanPage::init(ChannelsInfo info)
{
    Q_ASSERT(_core);
    const ChannelsCalibration & snapshot = _core->getCalibrationsSnapshot();
    init(info,snapshot);
}

void AScanPage::init(ChannelsInfo info,const ChannelsCalibration & snapshot)
{
    qDebug() << "Ascan init!";

    ui->ascanWidget->setChannelInfo(snapshot.getChannel(info._channel),info._displayChannel);
    std::vector<ChannelsInfo> infoList;
    for(uint8_t i=0; i<snapshot.getChannelsCount(); i++) {
        const Channel & chan = snapshot.getChannel(i);
        const auto & dispChannels = chan.getDisplayChannels();
        for(uint8_t j=0; j<dispChannels.size(); j++) {
            ChannelsInfo temp;
            temp._channel = i;
            temp._displayChannel = j;
            infoList.push_back(temp);
        }
    }

    ui->bscanWidget->setChannelsInfo(infoList);
    ui->bscanWidget->setActiveChannelData(snapshot.getChannel(info._channel),info);
    ui->controlPanel->setChannel(info);
    ui->controlPanel->init(snapshot);

    ui->channelSelector->init(snapshot);
    update();
}

void AScanPage::setCore(Core *core)
{
    Q_ASSERT(core);
    _core = core;
    ui->controlPanel->setCore(core);
    ui->channelSelector->setCore(core);
}

void AScanPage::switchToSelectedChannel()
{
    qDebug() << "Ascan switched channel!";
    const auto & info = ui->channelSelector->selectedChannel();
    setChannel(info);
}

void AScanPage::onDisplayPackage(QSharedPointer<DisplayPackage> package)
{
    ui->ascanWidget->onAScan(&(package->ascan));
    ui->bscanWidget->onBScan(&(package->bscan));
}

void AScanPage::onChannelChanged(Channel channel)
{
    ui->ascanWidget->onChannelChanged(channel);
    ui->bscanWidget->onChannelChanged(channel);
}

void AScanPage::setChannel(ChannelsInfo info)
{
    const ChannelsCalibration & snapshot = _core->getCalibrationsSnapshot();
    const Channel & chan = snapshot.getChannel(info._channel);
    _core->switchChannel(info);
    ui->ascanWidget->setChannelInfo(chan,info._displayChannel);
    // std::vector<ChannelsInfo> infoList;
    //infoList.push_back(info);
    //ui->bscanWidget->setChannelsInfo(infoList);
    ui->bscanWidget->setActiveChannelData(snapshot.getChannel(info._channel),info);
    ui->controlPanel->setChannel(info);
    ui->controlPanel->init(snapshot);
}
