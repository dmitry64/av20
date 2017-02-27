#include "ascanwidget.h"
#include "ui_ascanwidget.h"
#include <QPainter>
#include <QDebug>

void AScanWidget::setTVGCurve(TVGCurve *curve)
{
    if(_tvgCurve !=0) {
        delete _tvgCurve;
    }
    _tvgCurve = curve->clone();
}

AScanWidget::AScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanWidget)
{
    ui->setupUi(this);
    _fpsTimer.restart();
    _polygon.resize(ASCAN_SAMPLES_SIZE+2);
    _points.resize(ASCAN_SAMPLES_SIZE);
    _tvgCurvePen = QPen(QColor(250,10,10), 2);
    _tempCurvePen = QPen(QColor(10,10,250), 2);
    _ascanBrush = QBrush(QColor(80,80,200));
    _ascanPen = QPen(QColor(10,10,70), 1);
    _markerPos = 0;
    _markerValue = 0;
    _tvgCurve = 0;
    _tempCurve = 0;
    this->setAttribute(Qt::WA_OpaquePaintEvent);
}

AScanWidget::~AScanWidget()
{
    for(size_t i=0; i<_channels.size(); i++) {
        delete _channels[i];
    }
    _channels.clear();
    delete ui;
}

void AScanWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const int w = width();
    const int h = height();
    const int width = w - 64;
    const int height = h - 64;
    const double dHeight = height;
    const double step = width/static_cast<double>(_points.size());
    const int right = w - 32;
    const int left = 32;
    const int top = 32;
    const int bottom = h - 32;
    painter.fillRect(0,0,w,h,Qt::white);

    painter.setPen(Qt::black);
    painter.drawRect(0,0,w-1,h-1);

    uint8_t scale = 200;
    double scaleStep = width/static_cast<double>(scale);
    QFont font = painter.font();
    font.setPointSize(6);
    painter.setFont(font);
    for(uint8_t i=0; i<scale+1; i++) {
        uint8_t leng = 0;
        if(i%10 == 0) {
            leng = 16;
            //if(i!=scale) {
                painter.drawText(QPoint(left + i*scaleStep-6,28 + bottom),QString::number(i));
            //}
        } else {
            leng = 8;
        }
        painter.drawLine(QPoint(left + i*scaleStep,bottom),QPoint(i*scaleStep + left,leng + bottom));
    }

    painter.setPen(_ascanBrush.color());
    painter.drawLine(left,bottom,left,top);

    int scanScale = 10;
    double scanScaleStep = height / static_cast<double>(scanScale);

    for(uint16_t i=0; i<=scanScale; i++) {
        painter.drawLine(left-4,bottom - i * scanScaleStep,left,bottom - i * scanScaleStep);
        painter.drawText(left-28,bottom - i * scanScaleStep + 4,QString::number(i * 8.0/scanScale) + " V");
    }

    painter.setPen(_tvgCurvePen.color());
    painter.drawLine(right,bottom,right,top);


    int tvgScale = 10;
    double tvgScaleStep = height / static_cast<double>(tvgScale);

    for(uint16_t i=0; i<=tvgScale; i++) {
        painter.drawLine(right+4,bottom - i * tvgScaleStep,right,bottom - i * tvgScaleStep);
        painter.drawText(right+6,bottom - i * tvgScaleStep + 4,QString::number(i * 80/tvgScale) + " dB");
    }


/*
    // start
    _polygon[0] = QPoint(left,bottom);
    QPoint p2(0,bottom);
    for(uint16_t i=0; i<_points.size(); i++) {
        p2 = QPoint(qRound((_points[i].x())*step) + left, bottom - qRound(height*(_points[i].y() / 255.0)));
        _polygon[i+1] = (p2);
    }
    _polygon[ASCAN_SAMPLES_SIZE] = QPoint(right, p2.y());
    _polygon[ASCAN_SAMPLES_SIZE+1] = QPoint(right,bottom);
    // end
*/
    _polygon[0] = QPointF(left,bottom);
    QPointF p2(0,bottom);
    for(uint16_t i=0; i<_points.size(); i++) {
        p2 = QPointF(left + _points[i].x()*step, bottom - dHeight*(_points[i].y() / 256.0));
        _polygon[i+1] = (p2);
    }
    _polygon[ASCAN_SAMPLES_SIZE] = QPointF(right, p2.y());
    _polygon[ASCAN_SAMPLES_SIZE+1] = QPointF(right,bottom);

    painter.setPen(_ascanPen);
    painter.setBrush(_ascanBrush);
    //painter.drawPolygon(_polygon.data(),_polygon.size(),Qt::FillRule::WindingFill);
    //painter.drawPoints(_polygon.data(),_polygon.size());
    painter.drawPolygon(_polygon.data(),_polygon.size(),Qt::FillRule::OddEvenFill);
    double tvgStep = width/200.0;
    if(_tvgCurve!=0) {
        QPoint tvgStart(left, (h - 32) - _tvgCurve->getSample(0)*(h-64));

        painter.setPen(_tvgCurvePen);
        for(uint8_t i=0; i<200; i++) {
            int x = i*tvgStep + left;
            int y = (h - 32) - _tvgCurve->getSample(static_cast<double>(i) / 200.0) * (h-64) ;
            QPoint tvgNext = QPoint(x,y);
            painter.drawLine(tvgStart,tvgNext);
            tvgStart = tvgNext;
        }
    }

    if(_tempCurve != 0) {
        /*QPoint tvgStart(left, (h - 32) - _tempCurve->getSample(0)*(h-64)/2.0);
        painter.setPen(_tempCurvePen);
        for(uint8_t i=0; i<200; i++) {
            int x = i*tvgStep + left;
            int y = (h - 32) - _tempCurve->getSample(static_cast<double>(i) / 200.0) * (h-64);
            QPoint tvgNext = QPoint(x,y);
            painter.drawLine(tvgStart,tvgNext);
            tvgStart = tvgNext;
        }*/
        auto referencePoints = _tempCurve->getReferencePoints();
        for(size_t i=0; i<referencePoints.size(); i++) {
            QPoint p(left + referencePoints[i].first * (w - 64) ,(h - 32) - referencePoints[i].second * (h-64));
            painter.fillRect(QRect(p-QPoint(3,3),p+QPoint(3,3)),Qt::red);
        }
    }


    for(uint8_t i=0; i<_channels.size(); i++) {
        for(uint8_t j=0; j<_channels.at(i)->rx()->gates().size(); j++) {
            Gate gate = _channels.at(i)->rx()->gates()[j];
            int level = bottom - (gate._level * ((h-64)/255.0));
            painter.setPen(QPen(QColor( gate._level ,255 - gate._level, 0 ), 3));
            painter.drawLine(left + gate._start * scaleStep,level,left + gate._finish* scaleStep, level);
            painter.drawLine(left + gate._start * scaleStep,level,left + gate._start * scaleStep - 5, level + 5);
            painter.drawLine(left + gate._start * scaleStep,level,left + gate._start * scaleStep - 5, level - 5);
            painter.drawLine(left + gate._finish * scaleStep,level,left + gate._finish * scaleStep + 5, level + 5);
            painter.drawLine(left + gate._finish * scaleStep,level,left + gate._finish * scaleStep + 5, level - 5);
        }
    }

    painter.setPen(QPen(Qt::black, 1, Qt::PenStyle::DotLine));
    int markerHeight =  h -  (_markerValue / 255.0) * (h - 64) - 32;
    int markerPos = left + (_markerPos / 800.0) * width;
    painter.drawLine(left, markerHeight,markerPos, markerHeight);
    painter.drawLine(markerPos,markerHeight,markerPos,bottom);

    painter.setPen(QPen(Qt::red, 1));
    painter.drawLine(markerPos,bottom,markerPos,h-16);

    quint64 time = _fpsTimer.restart();
    double fps = 1000.0 / static_cast<double>(time);
    painter.drawText(QPoint(w - 140, 30),"fps: " + QString::number(fps,'f', 2));
}

void AScanWidget::setChannelsInfo(std::vector<Channel *> channels)
{
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

void AScanWidget::onAScan(AScanDrawData *scan)
{
    if(isVisible()) {
        for(uint8_t j=0; j<_channels.size(); j++) {
            uint8_t chan = scan->_channel;
            if(chan == _channels[j]->index()) {
                for(uint16_t i=0; i<scan->_samples.size(); i++) {
                    _points[i] = (QPoint(i,scan->_samples[i]));
                }
                _markerPos = scan->_markerPos;
                _markerValue = scan->_markerValue;
            }
        }
        update();
    }
}

void AScanWidget::drawTempTVG(TVGCurve *curve)
{
    Q_ASSERT(curve);
    if(_tempCurve!=0) {
        delete _tempCurve;
    }
    _tempCurve = curve->clone();
}

void AScanWidget::applyTempCurve()
{
    if(_tempCurve!=0) {
        if(_tvgCurve !=0) {
            delete _tvgCurve;
        }
        _tvgCurve = _tempCurve->clone();
        _tempCurve = 0;
    }
}

void AScanWidget::reset()
{
    if(_tvgCurve !=0) {
        delete _tvgCurve;
    }
    if(_tempCurve !=0) {
        delete _tempCurve;
    }
    _tvgCurve = 0;
    _tempCurve = 0;
    for(size_t i=0; i<_channels.size(); i++) {
        delete _channels.at(i);
    }
    _channels.clear();
}


uint8_t getBitFromByteArray(uint8_t * ptr, int bit) {
    int b = bit / 8;
    return (ptr[b] >> (bit % 8)) & 0b00000001;
}

uint8_t getTVGSample(uint8_t * ptr, int sampleNum) {
    int bit = sampleNum * 7;
    uint8_t res = 0x00;
    res |= getBitFromByteArray(ptr,bit);
    res |= getBitFromByteArray(ptr,bit+1) << 1;
    res |= getBitFromByteArray(ptr,bit+2) << 2;
    res |= getBitFromByteArray(ptr,bit+3) << 3;
    res |= getBitFromByteArray(ptr,bit+4) << 4;
    res |= getBitFromByteArray(ptr,bit+5) << 5;
    res |= getBitFromByteArray(ptr,bit+6) << 6;
    return res;
}

void AScanWidget::onChannelChanged(Channel * channel)
{
    Q_ASSERT(channel);
    for(uint8_t j=0; j<_channels.size(); j++) {
        uint8_t chan = channel->index();
        if(chan == _channels[j]->index())
        {
            Channel * chan = _channels[j];
            Q_ASSERT(chan);
            delete chan;
            _channels[j] = new Channel(channel);
            RxChannel * rx = channel->rx();
            Q_ASSERT(rx);
            TVGCurve * tvg = rx->getTvgCurve();
            Q_ASSERT(tvg);
            setTVGCurve(tvg);
        }
    }
    update();
}

