#ifndef ASCANWIDGET_H
#define ASCANWIDGET_H

#include <QWidget>
#include <atomic>
#include "device/definitions.h"
#include "device/channel.h"
#include <QElapsedTimer>

namespace Ui {
class AScanWidget;
}

class AScanWidget : public QWidget
{
    Q_OBJECT

    std::atomic_bool _ready;
    std::vector<QPoint> _points;
    std::vector<QPoint> _tvg;
    std::vector<QPoint> _polygon;
    std::vector<Channel> _channels;
    QElapsedTimer _fpsTimer;
public:
    explicit AScanWidget(QWidget *parent = 0);
    ~AScanWidget();
    void paintEvent(QPaintEvent * event);
    void setChannelsInfo(std::vector<Channel> channels);
public slots:
    void onAScan(AScan scan);
    void onTVG(TVG tvg);
private:
    Ui::AScanWidget *ui;
};

#endif // ASCANWIDGET_H
