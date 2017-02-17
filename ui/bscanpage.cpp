#include "bscanpage.h"
#include "ui_bscanpage.h"
#include <QDebug>

std::vector<BScanWidget*> BScanPage::getWidgetsByChannel(uint8_t chan)
{
    std::vector<BScanWidget*> result;
    for(int i=0; i<_bScanWidgets.size(); i++) {
        std::vector<Channel> channels = _bScanWidgets[i]->channels();
        for(int j=0; j<channels.size(); j++) {
            if(channels[j].index() == chan) {
                result.push_back(_bScanWidgets[i]);
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

}

BScanPage::~BScanPage()
{
    delete ui;
}

void BScanPage::setCore(Core *core)
{
    _core = core;
}

void BScanPage::init(ChannelsCalibration *snapshot)
{
    ui->channelSelectionWidget->init(snapshot);
}

void BScanPage::setChannles(std::vector<std::vector<Channel> > channelsConfiguration)
{
    for(int i=0; i<channelsConfiguration.size(); i++) {
        BScanWidget * widget = new BScanWidget(this);
        widget->setRestrictedToChannel(true);
        std::vector<Channel> info = channelsConfiguration[i];
        widget->setChannelsInfo(info);
        _bScanWidgets.push_back(widget);
        ui->bscanLayout->addWidget(widget);
    }
}

void BScanPage::onBScan(QSharedPointer<BScanDrawData> scan)
{
    uint8_t channel = scan->_channel;
    std::vector<BScanWidget*> widgets = getWidgetsByChannel(channel);
    //qDebug() << "size:"<<widgets.size();
    for(int i=0; i<widgets.size(); i++) {
        //widgets[i]->onBScan(scan);
    }
}

void BScanPage::onDisplayPackage(QSharedPointer<DisplayPackage> dp)
{
    uint8_t channel = dp->bscan._channel;
    std::vector<BScanWidget*> widgets = getWidgetsByChannel(channel);
    //qDebug() << "size:"<<widgets.size();
    for(int i=0; i<widgets.size(); i++) {
        widgets[i]->onBScan(&(dp->bscan));
    }
}

void BScanPage::onChannelChanged(Channel channel)
{
    for(int i=0; i<_bScanWidgets.size(); i++) {
        _bScanWidgets[i]->onChannelChanged(channel);
    }
}
