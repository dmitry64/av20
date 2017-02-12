#include "ascanpage.h"
#include "ui_ascanpage.h"

AScanPage::AScanPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanPage)
{
    ui->setupUi(this);
    connect(ui->channelSelector,SIGNAL(channelChanged(uint8_t)),this,SLOT(setChannel(uint8_t)));
    //connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)),ui->ascanWidget,SLOT()
}

AScanPage::~AScanPage()
{
    delete ui;
}

void AScanPage::init(uint8_t channel)
{
    DeviceCalibration * snapshot =  _core->getSnapshot();
    init(channel,snapshot);
}

void AScanPage::init(uint8_t channel, DeviceCalibration *snapshot)
{
    std::vector<Channel> channels;
    channels.push_back(*(snapshot->getChannel(channel)));
    ui->bscanWidget->setChannelsInfo(channels);
    ui->ascanWidget->setChannelsInfo(channels);
    ui->controlPanel->setChannel(channel);
    ui->controlPanel->init(snapshot);
    ui->channelSelector->init(snapshot);
}

void AScanPage::setCore(Core *core)
{
    _core = core;
    ui->controlPanel->setCore(core);
    ui->channelSelector->setCore(core);
}

void AScanPage::setAScanChannels(std::vector<Channel> channels)
{
    ui->ascanWidget->setChannelsInfo(channels);
}

void AScanPage::setBScanChannels(std::vector<Channel> channels)
{
    ui->bscanWidget->setChannelsInfo(channels);
}

void AScanPage::onAScan(QSharedPointer<AScanDrawData> scan)
{
    //ui->ascanWidget->onAScan(scan);
    //ui->bscanWidget->onAScan(scan);
}

void AScanPage::onBScan(QSharedPointer<BScanDrawData> scan)
{
    //ui->bscanWidget->onBScan(scan);
}

void AScanPage::onDisplayPackage(QSharedPointer<DisplayPackage> package)
{
    ui->ascanWidget->onAScan(&(package->ascan));
    ui->bscanWidget->onBScan(&(package->bscan));
}

void AScanPage::onTVG(TVG tvg)
{
    ui->ascanWidget->onTVG(tvg);
}

void AScanPage::onChannelChanged(Channel channel)
{
    ui->ascanWidget->onChannelChanged(channel);
    ui->bscanWidget->onChannelChanged(channel);
}

void AScanPage::setChannel(uint8_t channel)
{
    init(channel);
}
