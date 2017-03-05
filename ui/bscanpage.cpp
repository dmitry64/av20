#include "bscanpage.h"
#include "ui_bscanpage.h"
#include <QDebug>

std::vector<BScanWidget*> BScanPage::getWidgetsByChannel(uint8_t chan)
{
    std::vector<BScanWidget*> result;
    for(size_t i=0; i<_bScanWidgets.size(); i++) {
        std::vector<Channel> channels ;
        channels.push_back(_bScanWidgets[i]->channelData());
        for(size_t j=0; j<channels.size(); j++) {
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
    for(size_t i=0; i<_bScanWidgets.size(); i++) {
        BScanWidget * widget = _bScanWidgets.at(i);
        Q_ASSERT(widget);
        ui->bscanLayout->removeWidget(widget);
        delete widget;
    }

    _bScanWidgets.clear();
    delete ui;
}

void BScanPage::setCore(Core *core)
{
    _core = core;
    ui->channelSelectionWidget->setCore(_core);
}

void BScanPage::init(const ChannelsCalibration & snapshot)
{
    ui->channelSelectionWidget->init(snapshot);
    update();
}

void BScanPage::reset()
{
    for(size_t i=0; i<_bScanWidgets.size(); i++) {
        BScanWidget * widget = _bScanWidgets.at(i);
        Q_ASSERT(widget);
        widget->reset();
        ui->bscanLayout->removeWidget(widget);
        delete widget;
    }
    _bScanWidgets.clear();
}

void BScanPage::setChannles(std::vector<ChannelsInfo > channelsConfiguration, const ChannelsCalibration & snapshot)
{
    qDebug() << "BScan page setChannels";

    for(size_t i=0; i<_bScanWidgets.size(); i++) {
        BScanWidget * widget = _bScanWidgets.at(i);
        Q_ASSERT(widget);
        ui->bscanLayout->removeWidget(widget);
        delete widget;
    }

    _bScanWidgets.clear();

    for(size_t i=0; i<channelsConfiguration.size(); i++) {
        BScanWidget * widget = new BScanWidget(this);
        widget->setRestrictedToChannel(true);
        auto info = channelsConfiguration[i];
        widget->setChannelInfo(snapshot.getChannel(info._channel),info._displayChannel);
        _bScanWidgets.push_back(widget);
        ui->bscanLayout->addWidget(widget);
    }
}

void BScanPage::onDisplayPackage(QSharedPointer<DisplayPackage> dp)
{
    uint8_t channel = dp->bscan._channel;
    std::vector<BScanWidget*> widgets = getWidgetsByChannel(channel);
    //qDebug() << "size:"<<widgets.size();
    for(size_t i=0; i<widgets.size(); i++) {
        Q_ASSERT(widgets[i]);
        widgets[i]->onBScan(&(dp->bscan));
    }
}

void BScanPage::onChannelChanged(Channel channel)
{
    for(size_t i=0; i<_bScanWidgets.size(); i++) {
        _bScanWidgets[i]->onChannelChanged(channel);
    }
}
