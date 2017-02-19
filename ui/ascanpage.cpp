#include "ascanpage.h"
#include "ui_ascanpage.h"
#include <QDebug>

AScanPage::AScanPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanPage)
{
    ui->setupUi(this);
    connect(ui->channelSelector,SIGNAL(channelChanged(uint8_t)),this,SLOT(setChannel(uint8_t)));
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

void AScanPage::init(uint8_t channel)
{
    ChannelsCalibration * snapshot = _core->getCalibrationsSnapshot();
    init(channel,snapshot);
    delete snapshot;
}

void AScanPage::init(uint8_t channel, ChannelsCalibration *snapshot)
{
    qDebug() << "Ascan init!";
    std::vector<Channel *> channels;
    channels.push_back((snapshot->getChannel(channel)));
    ui->bscanWidget->setChannelsInfo(channels);
    ui->ascanWidget->setChannelsInfo(channels);
    ui->controlPanel->setChannel(channel);
    ui->controlPanel->init(snapshot);
    ui->channelSelector->init(snapshot);
    channels.clear();


    update();
}

void AScanPage::setCore(Core *core)
{
    _core = core;
    ui->controlPanel->setCore(core);
    ui->channelSelector->setCore(core);
}

void AScanPage::setAScanChannels(std::vector<Channel*> channels)
{
    ui->ascanWidget->setChannelsInfo(channels);
}

void AScanPage::setBScanChannels(std::vector<Channel*> channels)
{
    ui->bscanWidget->setChannelsInfo(channels);
}

void AScanPage::onDisplayPackage(QSharedPointer<DisplayPackage> package)
{
    ui->ascanWidget->onAScan(&(package->ascan));
    ui->bscanWidget->onBScan(&(package->bscan));
}

void AScanPage::onChannelChanged(Channel * channel)
{
    ui->ascanWidget->onChannelChanged(channel);
    ui->bscanWidget->onChannelChanged(channel);
}

void AScanPage::setChannel(uint8_t channel)
{
    ChannelsCalibration * snapshot = _core->getCalibrationsSnapshot();
    Q_ASSERT(snapshot);
    std::vector<Channel*> channels;
    channels.push_back((snapshot->getChannel(channel)));
    ui->bscanWidget->setChannelsInfo(channels);
    ui->ascanWidget->setChannelsInfo(channels);
    ui->controlPanel->setChannel(channel);
    ui->controlPanel->init(snapshot);
    update();
    delete snapshot;
    //init(channel);
}
