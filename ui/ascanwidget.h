#ifndef ASCANWIDGET_H
#define ASCANWIDGET_H

#include <QWidget>
#include <QPen>
#include <atomic>
#include "common/definitions.h"
#include "common/commonfunctions.h"
#include "device/channel/channel.h"
#include <QElapsedTimer>
#include "system/system.h"
#include "ascanplot.h"

namespace Ui
{
class AScanWidget;
}

class AScanWidget : public QWidget
{
    Q_OBJECT

    std::atomic_bool _ready;

    uint16_t _scale;

    AScanPlot * _plot;

    QPen _tvgCurvePen;
    QFont _scaleFont;
    QPen _ascanPen;
    QBrush _ascanBrush;

    int _scanScale;
    int _tvgScale;

private:
    void setTVGCurve(const TVGCurve *curve);
    void drawTimeScale(QPainter & painter, int width, int bottom, int left);
    void drawScanScale(QPainter & painter, int left, int bottom, int top, int height);
    void drawTvgScale(QPainter & painter, int right, int bottom, int top, int height);
    void drawFps(QPainter &painter, int posx, int posy);

public:
    explicit AScanWidget(QWidget *parent = 0);
    ~AScanWidget();
    void paintEvent(QPaintEvent * event);
    void reset();
    void setChannelInfo(const Channel &channel, DisplayChannelID dispChannelId);
public slots:
    void onAScan(const AScanDrawData &scan);
    void onChannelChanged(const Channel &channel);
private slots:
    void onFPSEnabledChanged(bool value);
private:
    Ui::AScanWidget *ui;
    void changeEvent(QEvent *event);
};

#endif // ASCANWIDGET_H
