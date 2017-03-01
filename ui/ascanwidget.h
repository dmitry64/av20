#ifndef ASCANWIDGET_H
#define ASCANWIDGET_H

#include <QWidget>
#include <QPen>
#include <atomic>
#include "device/definitions.h"
#include "device/commonfunctions.h"
#include "device/channel/channel.h"
#include <QElapsedTimer>

namespace Ui
{
class AScanWidget;
}

class AScanWidget : public QWidget
{
    Q_OBJECT

    std::atomic_bool _ready;
    uint16_t _markerPos;
    uint16_t _markerValue;
    uint16_t _scale;

    //std::vector<QPoint> _points;
    std::vector<QPoint> _polygon;
    std::vector<uint16_t> _samples;
    std::vector<Channel*> _channels;
    QElapsedTimer _fpsTimer;

    TVGCurve * _tvgCurve;

    QPen _tvgCurvePen;
    QFont _scaleFont;
    QPen _ascanPen;
    QBrush _ascanBrush;

private:
    void setTVGCurve(const TVGCurve *curve);
    void drawTimeScale(QPainter & painter, int width, int bottom, int left);
    void drawScanScale(QPainter & painter, int left, int bottom, int top, int height);
    void drawTvgScale(QPainter & painter, int right, int bottom, int top, int height);
    void drawTvgCurve(QPainter & painter, int width, int left, int bottom, int height);
    void drawGates(QPainter &painter, int width, int height, int left, int bottom);
    void drawAscan(QPainter &painter, int width, int height, int left, int bottom, int right);
    void drawMarker(QPainter &painter, int width, int height, int left, int bottom);
    void drawFps(QPainter &painter, int width);

public:
    explicit AScanWidget(QWidget *parent = 0);
    ~AScanWidget();
    void paintEvent(QPaintEvent * event);
    void setChannelsInfo(std::vector<Channel*> channels);
    //void applyTempCurve();
    void reset();
public slots:
    void onAScan(const AScanDrawData *scan);
    //void onTVG(TVG tvg);


    void onChannelChanged(Channel *channel);
private:
    Ui::AScanWidget *ui;
};

#endif // ASCANWIDGET_H
