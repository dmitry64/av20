#include "ascanpage.h"
#include "ui_ascanpage.h"
#include <QDebug>

void AScanPage::showEvent(QShowEvent *event)
{
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
    // delete snapshot;
}

void AScanPage::init(ChannelsInfo info,const ChannelsCalibration & snapshot)
{
    qDebug() << "Ascan init!";

    ui->ascanWidget->setChannelInfo(snapshot.getChannel(info._channel),info._displayChannel);
    //Q_ASSERT(snapshot);
    //std::vector<Channel *> channels;
    //Channel * chan = (snapshot->getChannel(channel));
    //Q_ASSERT(chan);
    //channels.push_back(chan);
    ui->bscanWidget->setChannelInfo(snapshot.getChannel(info._channel),info._displayChannel);
    //ui->ascanWidget->setChannelsInfo(channels);
    ui->controlPanel->setChannel(info);
    ui->controlPanel->init(snapshot);


    ui->channelSelector->init(snapshot);
    //channels.clear();
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
    ui->controlPanel->setChannel(info);
    ui->controlPanel->init(snapshot);
}
