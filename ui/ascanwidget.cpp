#include "ascanwidget.h"
#include "ui_ascanwidget.h"
#include <QPainter>
#include <QDebug>

void AScanWidget::setTVGCurve(const TVGCurve *curve)
{
    _plot->setTvgCurve(curve);
}

void AScanWidget::drawTimeScale(QPainter &painter, int width, int bottom, int left)
{
    painter.setPen(Qt::black);

    double scaleStep = width/static_cast<double>(_scale);
    painter.setFont(_scaleFont);
    for(uint8_t i=0; i<_scale+1; i++) {
        uint8_t leng = 0;
        if(i%10 == 0) {
            leng = 16;
            painter.drawText(QPoint(left + i*scaleStep-6,28 + bottom),QString::number(i));
        }
        else {
            leng = 8;
        }
        painter.drawLine(QPoint(left + i*scaleStep,bottom),QPoint(i*scaleStep + left,leng + bottom));
    }
}

void AScanWidget::drawScanScale(QPainter &painter, int left, int bottom, int top, int height)
{
    painter.setPen(_ascanBrush.color());
    painter.drawLine(left,bottom,left,top);

    const double scanScaleStep = height / static_cast<double>(_scanScale);

    for(uint16_t i=0; i<=_scanScale; i++) {
        painter.drawLine(left-4,bottom - i * scanScaleStep,left,bottom - i * scanScaleStep);
        painter.drawText(left-30,bottom - i * scanScaleStep + 4,QString::number(i * 1.2/_scanScale) + " V");
    }
}

void AScanWidget::drawTvgScale(QPainter &painter, int right, int bottom, int top, int height)
{
    painter.setPen(_tvgCurvePen.color());
    painter.drawLine(right,bottom,right,top);


    const double tvgScaleStep = height / static_cast<double>(_tvgScale);

    for(uint16_t i=0; i<=_tvgScale; i++) {
        painter.drawLine(right+4,bottom - i * tvgScaleStep,right,bottom - i * tvgScaleStep);
        painter.drawText(right+6,bottom - i * tvgScaleStep + 4,QString::number(i * 80/_tvgScale) + " dB");
    }
}

AScanWidget::AScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanWidget)
{
    ui->setupUi(this);

    _tvgCurvePen = QPen(QColor(250,10,10), 2);
    _tvgCurvePen.setCapStyle(Qt::RoundCap);
    _ascanBrush = QBrush(QColor(80,80,200));
    _ascanPen = QPen(QColor(10,10,70), 1);

    _scaleFont = QGuiApplication::font();
    _scaleFont.setPixelSize(8);
    _scale = 200;
    _scanScale = 10;
    _tvgScale = 10;
    const Settings * settings = System::getInstance()->getSettings();

    _plot = new AScanPlot(this);
    _plot->onFPSEnabledChanged(settings->getAscanFPSEnabled());
    _plot->show();
    connect(settings,SIGNAL(ascanFPSEnabledChanged(bool)),this,SLOT(onFPSEnabledChanged(bool)));
    this->setAttribute(Qt::WA_OpaquePaintEvent);
}

AScanWidget::~AScanWidget()
{
    delete ui;
}

void AScanWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    const QPalette & pal = this->palette();
    QColor bgColor = pal.color(QPalette::Window);
    const QColor inverted(255-bgColor.red(),255-bgColor.green(),bgColor.blue());
    _ascanBrush.setColor(inverted);
    _plot->setAScanColor(inverted);
    bgColor = bgColor.lighter(170.0f);
    _plot->setBgColor(bgColor);

    const int w = width();
    const int h = height();
    const int width = w - 64;
    const int height = h - 40;

    const int right = w - 32;
    const int left = 32;
    const int top = 8;
    const int bottom = h - 32;
    painter.fillRect(0,0,w,h,bgColor);

    painter.setPen(Qt::black);
    painter.drawRect(0,0,w-1,h-1);

    _plot->setGeometry(left+1,top,width-1,height);

    drawTimeScale(painter,width,bottom,left);
    drawScanScale(painter,left,bottom,top,height);
    drawTvgScale(painter,right,bottom,top,height);
}

void AScanWidget::setChannelInfo(const Channel & channel, DisplayChannelID dispChannelId)
{
    _plot->setChannelInfo(channel,dispChannelId);
}

void AScanWidget::onAScan(const AScanDrawData & scan)
{
    _plot->onAScan(scan);
}

void AScanWidget::reset()
{
    _plot->reset();
}

void AScanWidget::onChannelChanged(const Channel & channel)
{
    _plot->onChannelChanged(channel);
}

void AScanWidget::onFPSEnabledChanged(bool value)
{
    _plot->onFPSEnabledChanged(value);
}
