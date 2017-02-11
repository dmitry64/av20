#ifndef BSCANWIDGET_H
#define BSCANWIDGET_H

#include <QWidget>
#include <queue>
#include "device/definitions.h"
#include "device/channel.h"

namespace Ui {
class BScanWidget;
}

class BScanWidget : public QWidget
{
    Q_OBJECT

    std::vector< std::pair< std::vector<BScanDrawData> , int> > _scans;
    std::vector<Channel> _channels;

    std::vector< QLinearGradient > _gradients;

    int _width;
    //int _start;
    int _end;
private:
    bool channelSelected(uint8_t chan);

public:
    explicit BScanWidget(QWidget *parent = 0);
    ~BScanWidget();
    void paintEvent(QPaintEvent * event);

    void setChannelsInfo(std::vector<Channel> channels);
    std::vector<Channel> channels() const;

public slots:
    void onBScan(BScanDrawData * scan);
private:
    Ui::BScanWidget *ui;
};

#endif // BSCANWIDGET_H
