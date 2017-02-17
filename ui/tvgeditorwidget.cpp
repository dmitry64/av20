#include "tvgeditorwidget.h"
#include "ui_tvgeditorwidget.h"

TVGEditorWidget::TVGEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TVGEditorWidget)
{
    ui->setupUi(this);
}

TVGEditorWidget::~TVGEditorWidget()
{
    delete ui;
}

void TVGEditorWidget::init(uint8_t channel)
{
    ChannelsCalibration * snapshot =  _core->getCalibrationsSnapshot();
    init(channel,snapshot);
    delete snapshot;
}

void TVGEditorWidget::init(uint8_t channel, ChannelsCalibration *snapshot)
{
    std::vector<Channel> channels;
    channels.push_back(*(snapshot->getChannel(channel)));
    ui->aScanWidget->setChannelsInfo(channels);
    ui->channelSelector->init(snapshot);
    update();
}

void TVGEditorWidget::setCore(Core *core)
{
    _core = core;
    ui->channelSelector->setCore(core);
}

void TVGEditorWidget::onDisplayPackage(QSharedPointer<DisplayPackage> package)
{
    ui->aScanWidget->onAScan(&(package->ascan));
}

void TVGEditorWidget::onChannelChanged(Channel channel)
{
    ui->aScanWidget->onChannelChanged(channel);
}

void TVGEditorWidget::setChannel(uint8_t channel)
{
    init(channel);
}

