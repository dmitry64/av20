#ifndef ASCANWIDGET_H
#define ASCANWIDGET_H

#include <QWidget>
#include <QPen>
#include <atomic>
#include "device/definitions.h"
#include "device/commonfunctions.h"
#include "device/channel/channel.h"
#include <QElapsedTimer>

namespace Ui {
class AScanWidget;
}

class AScanWidget : public QWidget
{
    Q_OBJECT

    std::atomic_bool _ready;
    uint16_t _markerPos;
    uint16_t _markerValue;
    std::vector<QPoint> _points;
    //std::vector<QPoint> _tvg;
    std::vector<QPointF> _polygon;
    std::vector<Channel*> _channels;
    QElapsedTimer _fpsTimer;

    TVGCurve * _tvgCurve;

    TVGCurve * _tempCurve;

    QPen _tvgCurvePen;
    QPen _tempCurvePen;
    QPen _ascanPen;
    QBrush _ascanBrush;

private:
    void setTVGCurve(TVGCurve * curve);

public:
    explicit AScanWidget(QWidget *parent = 0);
    ~AScanWidget();
    void paintEvent(QPaintEvent * event);
    void setChannelsInfo(std::vector<Channel*> channels);
    void drawTempTVG(TVGCurve * curve);
    void applyTempCurve();
    void reset();
public slots:
    void onAScan(AScanDrawData * scan);
    //void onTVG(TVG tvg);


    void onChannelChanged(Channel *channel);
private:
    Ui::AScanWidget *ui;
};

#endif // ASCANWIDGET_H
