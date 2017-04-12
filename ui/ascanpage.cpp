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
    _current._channel = 0;
    _current._displayChannel = 0;
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

void AScanPage::initBScan(ChannelsInfo info, const Channel& ch, const ChannelsCalibration& snapshot)
{
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
    ui->bscanWidget->setActiveChannelData(ch,info);
}

void AScanPage::init(ChannelsInfo info,const ChannelsCalibration & snapshot)
{
    logEvent("AScanPage","Initializing");
    const Channel & ch = snapshot.getChannel(info._channel);
    _current = info;
    ui->ascanWidget->setChannelInfo(snapshot.getChannel(info._channel),info._displayChannel);
    initBScan(info, ch, snapshot);
    ui->controlPanel->setChannel(info);
    ui->controlPanel->init(ch);
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
    logEvent("AScanPage","Switched channel");
    const auto & info = ui->channelSelector->selectedChannel();
    setChannel(info);
}

void AScanPage::onDisplayPackage(QSharedPointer<DisplayPackage> package)
{
    const auto & bscan = package->_bscan;
    ui->bscanWidget->onBScan(bscan);
    if(package->_ascan._channel==_current._channel) {
        const auto & ascan = package->_ascan;
        ui->ascanWidget->onAScan(ascan);
        int marker = qRound((static_cast<double>(ascan._markerPos)/800.0) * 200.0);
        ui->aScanInfoWidget->setHValue(marker);
    }
}

void AScanPage::onChannelChanged(Channel channel)
{
    ui->bscanWidget->onChannelChanged(channel);
    if(channel.index()==_current._channel) {
        ui->ascanWidget->onChannelChanged(channel);
    }
    ui->controlPanel->init(channel);
}

void AScanPage::setChannel(ChannelsInfo info)
{
    _current = info;
    const ChannelsCalibration & snapshot = _core->getCalibrationsSnapshot();
    const Channel & chan = snapshot.getChannel(info._channel);

    _core->switchChannel(info);
    ui->ascanWidget->setChannelInfo(chan,info._displayChannel);
    ui->bscanWidget->setActiveChannelData(snapshot.getChannel(info._channel),info);
    ui->aScanInfoWidget->setChannel(chan, _current._displayChannel);
    ui->controlPanel->setChannel(info);
    ui->controlPanel->init(chan);
}
