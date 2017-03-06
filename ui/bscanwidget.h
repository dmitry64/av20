#ifndef BSCANWIDGET_H
#define BSCANWIDGET_H

#include <QWidget>
#include <queue>
#include <map>
#include "device/definitions.h"
#include "device/commonfunctions.h"
#include "device/channel/channel.h"
#include <map>

namespace Ui
{
class BScanWidget;
}

class BScanWidget : public QWidget
{
    Q_OBJECT

    //std::vector< std::pair< std::vector< std::vector<BScanDrawSample> > , uint8_t> > _samples;
    std::vector< std::pair< ChannelsInfo, BScanDrawArray > > _samplesArray;
    int _width;
    int _end;

    bool _restrictedToChannel;
    Channel _channelData;
    ChannelsInfo _info;
private:

public:
    explicit BScanWidget(QWidget *parent = 0);
    ~BScanWidget();
    void paintEvent(QPaintEvent * event);

    void setRestrictedToChannel(bool flag);
    void reset();

    void setChannelsInfo(std::vector<ChannelsInfo> selectedChannels);
    void setActiveChannelData(const Channel &channel, ChannelsInfo info);
    Channel channelData() const;

public slots:
    void onBScan(BScanDrawData * scan);
    void onChannelChanged(Channel channel);
private:
    Ui::BScanWidget *ui;
};

#endif // BSCANWIDGET_H
