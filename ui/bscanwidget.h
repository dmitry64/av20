#ifndef BSCANWIDGET_H
#define BSCANWIDGET_H

#include <QWidget>
#include <queue>
#include <map>
#include "device/definitions.h"
#include "device/channel.h"

namespace Ui {
class BScanWidget;
}

class BScanWidget : public QWidget
{
    Q_OBJECT

    //std::vector< std::pair< std::vector<BScanDrawData> , int> > _scans;
    std::vector<Channel> _channels;

    //std::map<uint8_t, std::vector<QLinearGradient> > _gradients;
    std::vector< std::pair< std::vector<QLinearGradient> , int> > _gradients;

    int _width;
    int _end;

    bool _restrictedToChannel;
private:
    bool channelSelected(uint8_t chan);

public:
    explicit BScanWidget(QWidget *parent = 0);
    ~BScanWidget();
    void paintEvent(QPaintEvent * event);

    void setChannelsInfo(std::vector<Channel> channels);
    void setRestrictedToChannel(bool flag);
    std::vector<Channel> channels() const;

public slots:
    void onBScan(BScanDrawData * scan);
private:
    Ui::BScanWidget *ui;
};

#endif // BSCANWIDGET_H
