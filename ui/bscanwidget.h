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

    std::vector< std::pair< std::vector<AScan> , int> > _scans;
    std::vector<Channel> _channels;

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
    void onAScan(AScan scan);
private:
    Ui::BScanWidget *ui;
};

#endif // BSCANWIDGET_H
