#include "ascanwidget.h"
#include "ui_ascanwidget.h"
#include <QPainter>
#include <QDebug>

void AScanWidget::setTVGCurve(const TVGCurve *curve)
{
    if(_tvgCurve !=0) {
        delete _tvgCurve;
    }
    _tvgCurve = curve->clone();
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

    int scanScale = 10;
    double scanScaleStep = height / static_cast<double>(scanScale);

    for(uint16_t i=0; i<=scanScale; i++) {
        painter.drawLine(left-4,bottom - i * scanScaleStep,left,bottom - i * scanScaleStep);
        painter.drawText(left-30,bottom - i * scanScaleStep + 4,QString::number(i * 1.2/scanScale) + " V");
    }
}

void AScanWidget::drawTvgScale(QPainter &painter, int right, int bottom, int top, int height)
{
    painter.setPen(_tvgCurvePen.color());
    painter.drawLine(right,bottom,right,top);

    int tvgScale = 10;
    double tvgScaleStep = height / static_cast<double>(tvgScale);

    for(uint16_t i=0; i<=tvgScale; i++) {
        painter.drawLine(right+4,bottom - i * tvgScaleStep,right,bottom - i * tvgScaleStep);
        painter.drawText(right+6,bottom - i * tvgScaleStep + 4,QString::number(i * 80/tvgScale) + " dB");
    }
}

void AScanWidget::drawTvgCurve(QPainter &painter,int width,int left, int bottom, int height)
{
    if(_tvgCurve!=0) {
        int scale = 200;
        double tvgStep = width/static_cast<double>(scale);
        QPoint tvgStart(left, bottom - _tvgCurve->getSample(0)*height);
        painter.setPen(_tvgCurvePen);
        for(uint8_t i=0; i<scale; i++) {
            int x = i*tvgStep + left;
            int y = bottom - _tvgCurve->getSample(static_cast<double>(i) / scale) * (height) ;
            QPoint tvgNext = QPoint(x,y);
            painter.drawLine(tvgStart,tvgNext);
            tvgStart = tvgNext;
        }

        auto referencePoints = _tvgCurve->getReferencePoints();
        painter.setPen(Qt::black);
        painter.setBrush(QBrush(Qt::green));
        for(size_t i=0; i<referencePoints.size(); i++) {
            QPoint p(left + referencePoints[i].first * width ,bottom - referencePoints[i].second * (height));
           //painter.fillRect(QRect(p-QPoint(3,3),p+QPoint(3,3)),Qt::black);
            painter.drawEllipse(QRect(p-QPoint(3,3),p+QPoint(3,3)));
        }
    }
}

void AScanWidget::drawGates(QPainter &painter, int width, int height, int left, int bottom)
{
    double scaleStep = width/static_cast<double>(_scale);
    uint8_t channelsCount = _channels.size();
    Q_ASSERT(channelsCount<8);
    for(uint8_t i=0; i<channelsCount; i++) {
        const auto & gates = _channels[i]->rx()->gates();
        uint8_t gatesCount = gates.size();
        for(uint8_t j=0; j<gatesCount; j++) {
            Gate gate = gates[j];
            int level = bottom - (gate._level * (height/255.0));
            QPen gatePen = QPen(getColorByLevel(gate._level),3);
            gatePen.setCapStyle(Qt::RoundCap);
            painter.setPen(gatePen);

            painter.drawLine(left + gate._start * scaleStep,level,left + gate._finish* scaleStep, level);
            painter.drawLine(left + gate._start * scaleStep,level,left + gate._start * scaleStep - 5, level + 5);
            painter.drawLine(left + gate._start * scaleStep,level,left + gate._start * scaleStep - 5, level - 5);
            painter.drawLine(left + gate._finish * scaleStep,level,left + gate._finish * scaleStep + 5, level + 5);
            painter.drawLine(left + gate._finish * scaleStep,level,left + gate._finish * scaleStep + 5, level - 5);
        }
    }
}

void AScanWidget::drawAscan(QPainter &painter, int width, int height, int left, int bottom, int right)
{
    painter.setPen(_ascanPen);
    painter.setBrush(_ascanBrush);

    painter.drawLine(left,bottom,right,bottom);
    const double step = width/800.0;
    uint16_t size = _samples.size();
    uint16_t currentCount = 0;
    uint16_t currentStart = 0;
    for(uint16_t i=0; i<size; i++) {
        if(_samples[i] > 0) {
            if(currentCount==0) {
                _polygon[currentCount] = QPoint(left + (i-1)*step, bottom);
                currentCount++;
            }
            _polygon[currentCount] = QPoint(left + i*step, bottom - height*(_samples[i] / 256.0));
            currentCount++;
        } else {
            if(currentCount!=0) {
                _polygon[currentCount] = QPoint(left + (i+1)*step, bottom);
                currentCount++;
                painter.drawPolygon(_polygon.data(),currentCount, Qt::FillRule::OddEvenFill);
                currentStart = i;
                currentCount = 0;
            }
        }
    }
    if(currentCount!=0) {
        _polygon[currentCount] = QPoint(left + 800*step, bottom - height*(_samples[size-1] / 256.0));
        currentCount++;
        painter.drawPolygon(_polygon.data(),currentCount, Qt::FillRule::OddEvenFill);
    }

}

void AScanWidget::drawMarker(QPainter &painter, int width, int height, int left, int bottom)
{
    painter.setPen(QPen(Qt::black, 1, Qt::PenStyle::DotLine));
    int markerHeight = (bottom) -  (_markerValue / 255.0) * height ;
    int markerPos = left + (_markerPos / 800.0) * width;
    painter.drawLine(left, markerHeight,markerPos, markerHeight);
    painter.drawLine(markerPos,markerHeight,markerPos,bottom);
    painter.setPen(Qt::red);
    painter.drawLine(markerPos,bottom,markerPos,bottom+16);
}

void AScanWidget::drawFps(QPainter &painter, int posx, int posy)
{
    quint64 time = _fpsTimer.nsecsElapsed();
    _fpsTimer.start();
    double fps = 1/(static_cast<double>(time) / 1000000000.0);
    painter.drawText(QPoint(posx, posy),"fps: " + QString::number(fps,'f', 3));
}

AScanWidget::AScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanWidget)
{
    ui->setupUi(this);
    _fpsTimer.restart();
    _polygon.resize(ASCAN_SAMPLES_SIZE+2);
    //_points.resize(ASCAN_SAMPLES_SIZE);
    _tvgCurvePen = QPen(QColor(250,10,10), 2);
    _tvgCurvePen.setCapStyle(Qt::RoundCap);
    //_tempCurvePen = QPen(QColor(10,10,250), 2);
    _ascanBrush = QBrush(QColor(80,80,200));
    _ascanPen = QPen(QColor(10,10,70), 1);

    _markerPos = 0;
    _markerValue = 0;
    _tvgCurve = 0;
    _scaleFont = QGuiApplication::font();
    _scaleFont.setPixelSize(8);
    //_tempCurve = 0;
    _scale = 200;
    this->setAttribute(Qt::WA_OpaquePaintEvent);
}

AScanWidget::~AScanWidget()
{
    for(size_t i=0; i<_channels.size(); i++) {
        delete _channels[i];
    }
    if(_tvgCurve !=0) {
        delete _tvgCurve;
    }
    _channels.clear();
    delete ui;
}

void AScanWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    const int w = width();
    const int h = height();
    const int width = w - 64;
    const int height = h - 40;

    const int right = w - 32;
    const int left = 32;
    const int top = 8;
    const int bottom = h - 32;
    painter.fillRect(0,0,w,h,Qt::white);

    painter.setPen(Qt::black);
    painter.drawRect(0,0,w-1,h-1);

    drawTimeScale(painter,width,bottom,left);
    drawScanScale(painter,left,bottom,top,height);
    drawTvgScale(painter,right,bottom,top,height);
    drawAscan(painter,width,height,left,bottom,right);
    drawTvgCurve(painter,width,left,bottom,height);
    drawGates(painter,width,height,left,bottom);
    drawMarker(painter,width,height,left,bottom);
    drawFps(painter,width - 50, 16);
}

void AScanWidget::setChannelsInfo(std::vector<Channel *> channels)
{
    if(_tvgCurve !=0) {
        delete _tvgCurve;
    }
    _tvgCurve = 0;
    for(size_t i=0; i<_channels.size(); i++) {
        delete _channels.at(i);
    }
    _channels.clear();
    std::vector<Channel*> result;
    for(size_t i=0; i<channels.size(); i++) {
        result.push_back(new Channel(channels.at(i)));
    }
    _channels = result;
    if(channels.size() > 0) {
        setTVGCurve(channels[0]->rx()->getTvgCurve());
    }
}

void AScanWidget::onAScan(const AScanDrawData *scan)
{
    if(isVisible()) {
        for(uint8_t j=0; j<_channels.size(); j++) {
            uint8_t chan = scan->_channel;
            if(chan == _channels[j]->index()) {
                _samples = scan->_samples;

                _markerPos = scan->_markerPos;
                _markerValue = scan->_markerValue;
            }
        }
        update();
    }
}

void AScanWidget::reset()
{
    if(_tvgCurve !=0) {
        delete _tvgCurve;
    }
    _tvgCurve = 0;
    for(size_t i=0; i<_channels.size(); i++) {
        delete _channels.at(i);
    }
    _channels.clear();
}

void AScanWidget::onChannelChanged(Channel * channel)
{
    Q_ASSERT(channel);
    for(uint8_t j=0; j<_channels.size(); j++) {
        uint8_t chan = channel->index();
        if(chan == _channels[j]->index()) {
            Channel * chan = _channels[j];
            Q_ASSERT(chan);
            delete chan;
            _channels[j] = new Channel(channel);
            RxChannel * rx = channel->rx();
            Q_ASSERT(rx);
            const TVGCurve * tvg = rx->getTvgCurve();
            Q_ASSERT(tvg);
            setTVGCurve(tvg);
        }
    }
    update();
}
