#ifndef BSCANWIDGET_H
#define BSCANWIDGET_H

#include <QWidget>
#include <queue>
#include <map>
#include "device/definitions.h"
#include "device/commonfunctions.h"
#include "device/channel/channel.h"

namespace Ui {
class BScanWidget;
}

class BScanWidget : public QWidget
{
    Q_OBJECT

    std::vector<Channel*> _channels;
    std::vector< std::pair< std::vector< std::vector<BScanDrawSample> > , int> > _samples;

    int _width;
    int _end;

    bool _restrictedToChannel;
private:
    bool channelSelected(uint8_t chan);

public:
    explicit BScanWidget(QWidget *parent = 0);
    ~BScanWidget();
    void paintEvent(QPaintEvent * event);

    void setChannelsInfo(std::vector<Channel *> channels);
    void setRestrictedToChannel(bool flag);
    void reset();
    std::vector<Channel *> channels() const;


public slots:
    void onBScan(BScanDrawData * scan);
    void onChannelChanged(Channel *channel);
private:
    Ui::BScanWidget *ui;
};

#endif // BSCANWIDGET_H
