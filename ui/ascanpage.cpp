#include "ascanpage.h"
#include "ui_ascanpage.h"

AScanPage::AScanPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanPage)
{
    ui->setupUi(this);
    connect(ui->channelSelector,SIGNAL(channelChanged(uint8_t)),this,SLOT(setChannel(uint8_t)));
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

}

void AScanPage::setCore(Core *core)
{
    _core = core;
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

void AScanPage::onAScan(AScan scan)
{
    ui->ascanWidget->onAScan(scan);
    ui->bscanWidget->onAScan(scan);
}

void AScanPage::onTVG(TVG tvg)
{
    ui->ascanWidget->onTVG(tvg);
}

void AScanPage::setChannel(uint8_t channel)
{
    init(channel);
}
