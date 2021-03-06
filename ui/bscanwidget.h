#ifndef BSCANWIDGET_H
#define BSCANWIDGET_H

#include <QWidget>
#include <queue>
#include <map>
#include "common/definitions.h"
#include "common/commonfunctions.h"
#include "device/channel/channel.h"
#include <map>

namespace Ui
{
class BScanWidget;
}

class BScanWidget : public QWidget
{
    Q_OBJECT

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

    void setChannelsInfo(const std::vector<ChannelsInfo> &selectedChannels);
    void setActiveChannelData(const Channel &channel, const ChannelsInfo &info);
    Channel channelData() const;

public slots:
    void onBScan(const BScanDrawData &scan);
    void onChannelChanged(Channel channel);
private:
    Ui::BScanWidget *ui;
    void drawGates(const double hstep, QPainter &painter, const int right);
    void changeEvent(QEvent *event);
};

#endif // BSCANWIDGET_H
