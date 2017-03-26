#ifndef ASCANWIDGET_H
#define ASCANWIDGET_H

#include <QWidget>
#include <QPen>
#include <atomic>
#include "common/definitions.h"
#include "common/commonfunctions.h"
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

    std::vector<QPoint> _polygon;
    std::vector<uint16_t> _samples;

    QElapsedTimer _fpsTimer;

    TVGCurve * _tvgCurve;

    QPen _tvgCurvePen;
    QFont _scaleFont;
    QPen _ascanPen;
    QBrush _ascanBrush;

    Channel _channelData;
    DisplayChannelID _displayChannelId;

private:
    void setTVGCurve(const TVGCurve *curve);
    void drawTimeScale(QPainter & painter, int width, int bottom, int left);
    void drawScanScale(QPainter & painter, int left, int bottom, int top, int height);
    void drawTvgScale(QPainter & painter, int right, int bottom, int top, int height);
    void drawTvgCurve(QPainter & painter, int width, int left, int bottom, int height);
    void drawGates(QPainter &painter, int width, int height, int left, int bottom);
    void drawAscan(QPainter &painter, int width, int height, int left, int bottom, int right);
    void drawMarker(QPainter &painter, int width, int height, int left, int bottom);
    void drawFps(QPainter &painter, int posx, int posy);

public:
    explicit AScanWidget(QWidget *parent = 0);
    ~AScanWidget();
    void paintEvent(QPaintEvent * event);
    void reset();
    void setChannelInfo(const Channel &channel, DisplayChannelID dispChannelId);
public slots:
    void onAScan(const AScanDrawData *scan);
    void onChannelChanged(const Channel &channel);
private:
    Ui::AScanWidget *ui;
};

#endif // ASCANWIDGET_H
