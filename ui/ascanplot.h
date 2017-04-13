#ifndef ASCANPLOT_H
#define ASCANPLOT_H

#include "common/definitions.h"
#include <QWidget>
#include <QPen>
#include <QBrush>
#include "device/tvg/tvgcurve.h"
#include "device/channel/channel.h"
#include <vector>

class AScanPlot : public QWidget
{
    Q_OBJECT

    QPen _ascanPen;
    QBrush _ascanBrush;
    QPen _tvgCurvePen;
    uint16_t _scale;

    QColor _bgColor;
    uint16_t _markerPos;
    uint16_t _markerValue;

    Channel _channelData;
    DisplayChannelID _displayChannelId;

    std::vector<QPoint> _polygon;
    std::vector<uint16_t> _samples;
    std::vector<double> _tvgSamples;
    std::vector<std::pair<double,double> > _tvgReferencePoints;

    QElapsedTimer _fpsTimer;

    bool _drawFPS;
private:
    void paintEvent(QPaintEvent * event);
    void drawAscan(QPainter &painter, int width, int height);
    void drawTvgCurve(QPainter &painter, int width, int height);
    void drawMarker(QPainter &painter, int width, int height);
    void drawGates(QPainter &painter, int width, int height);

    void drawFps(QPainter &painter, int posx, int posy);
    void changeEvent(QEvent *event);
public:
    explicit AScanPlot(QWidget *parent = 0);
    ~AScanPlot();
    void onAScan(const AScanDrawData &scan);
    void setTvgCurve(const TVGCurve *curve);
    void reset();

    void setBgColor(const QColor &bgColor);
    void setAScanColor(const QColor &ascanColor);
    void setChannelInfo(const Channel &channel, DisplayChannelID dispChannelId);
    void setScale(const uint16_t &scale);

    void onChannelChanged(const Channel &channel);
    void onFPSEnabledChanged(bool value);
signals:

public slots:
};

#endif // ASCANPLOT_H
