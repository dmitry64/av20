#include "bscanpage.h"
#include "ui_bscanpage.h"
#include <QDebug>

std::vector<BScanWidget*> BScanPage::getWidgetsByChannel(uint8_t chan)
{
    std::vector<BScanWidget*> result;
    for(auto it=_bScanWidgets.begin(); it!=_bScanWidgets.end(); it++) {
        std::vector<Channel> channels;
        channels.push_back(it.operator*()->channelData());
        for(size_t j=0; j<channels.size(); j++) {
            if(channels[j].index() == chan) {
                result.push_back(it.operator*());
            }
        }
    }
    return result;
}

BScanPage::BScanPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanPage)
{
    ui->setupUi(this);
    connect(ui->channelSelectionWidget,SIGNAL(channelChanged(ChannelsInfo)),this,SLOT(setChannel(ChannelsInfo)));
}

BScanPage::~BScanPage()
{
    for(auto it=_bScanWidgets.begin(); it!=_bScanWidgets.end(); it++) {
        BScanWidget * widget = it.operator*();
        Q_ASSERT(widget);
        ui->bscanLayout->removeWidget(widget);
        delete widget;
    }

    _bScanWidgets.clear();
    delete ui;
}

void BScanPage::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}

void BScanPage::setCore(Core *core)
{
    _core = core;
    ui->channelSelectionWidget->setCore(_core);
}

void BScanPage::init(const ChannelsCalibration & snapshot)
{
    logEvent("BScanPage","Initializing");
    ui->channelSelectionWidget->init(snapshot);
    update();
}

void BScanPage::reset()
{
    logEvent("BScanPage","Reset");
    for(auto it=_bScanWidgets.begin(); it!=_bScanWidgets.end(); it++) {
        BScanWidget * widget = it.operator*();
        Q_ASSERT(widget);
        widget->reset();
        ui->bscanLayout->removeWidget(widget);
        delete widget;
    }
    _bScanWidgets.clear();
}

void BScanPage::setChannles(const std::vector<ChannelsInfo > &channelsConfiguration, const ChannelsCalibration & snapshot)
{
    logEvent("BScanPage","Set channels");

    for(auto it=_bScanWidgets.begin(); it!=_bScanWidgets.end(); it++) {
        BScanWidget * widget = it.operator*();
        Q_ASSERT(widget);
        ui->bscanLayout->removeWidget(widget);
        delete widget;
    }

    _bScanWidgets.clear();

    for(auto it=channelsConfiguration.begin(); it!=channelsConfiguration.end(); it++) {
        BScanWidget * widget = new BScanWidget(this);
        widget->setRestrictedToChannel(true);
        const ChannelsInfo & info = it.operator*();
        std::vector<ChannelsInfo> infoList;
        infoList.push_back(info);
        widget->setChannelsInfo(infoList);
        widget->setActiveChannelData(snapshot.getChannel(info._channel),info);
        _bScanWidgets.push_back(widget);
        ui->bscanLayout->addWidget(widget);
    }
}

void BScanPage::onDisplayPackage(QSharedPointer<DisplayPackage> dp)
{
    uint8_t channel = dp->_bscan._info._channel;
    Q_ASSERT(channel<8);
    const std::vector<BScanWidget*> & widgets = getWidgetsByChannel(channel);
    for(auto it=widgets.begin(); it!=widgets.end(); it++) {
        BScanWidget * wid = it.operator*();
        Q_ASSERT(wid);
        wid->onBScan(dp->_bscan);
    }
}

void BScanPage::onChannelChanged(Channel channel)
{
    for(auto it=_bScanWidgets.begin(); it!=_bScanWidgets.end(); it++) {
        it.operator*()->onChannelChanged(channel);
    }
}

void BScanPage::setChannel(ChannelsInfo info)
{
    _core->switchChannel(info);
}
