#include "ascanwidget.h"
#include "ui_ascanwidget.h"
#include <QPainter>
#include <QDebug>

AScanWidget::AScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanWidget)
{
    ui->setupUi(this);
    _fpsTimer.restart();
    _polygon.resize(ASCAN_SAMPLES_SIZE+2);
    _points.resize(ASCAN_SAMPLES_SIZE);
    _tvgCurvePen = QPen(QColor(250,10,10), 2);
    _ascanBrush = QBrush(QColor(80,80,200));
    _ascanPen = QPen(QColor(10,10,70), 1);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
}

AScanWidget::~AScanWidget()
{
    delete ui;
}

void AScanWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const int w = width();
    const int h = height();
    const int width = w - 64;
    const double step = width/800.0;
    //QPoint bottomLeft(32,h - 32);
    //QPoint topRight(w - 32, 0);
    const int right = w - 32;
    const int left = 32;
    const int top = 32;
    const int bottom = h - 32;
    painter.fillRect(0,0,w,h,Qt::white);

    painter.setPen(Qt::black);
    //painter.fillRect(left,bottom,w,h, Qt::white);//QRect(bottomLeft,topRight),Qt::white);
    painter.drawRect(0,0,w-1,h-1);

    //painter.fillRect(0,bottom,w, h - 24,Qt::white);
    uint8_t scale = 200;
    double scaleStep = width/static_cast<double>(scale);
    for(uint8_t i=0; i<scale+1; i++) {
        uint8_t leng = 0;
        if(i%10 == 0) {
            leng = 16;
            if(i!=scale) {
                painter.drawText(QPoint(left + i*scaleStep+2,24 + bottom),QString::number(i));
            }
        } else {
            leng = 8;
        }
        painter.drawLine(QPoint(left + i*scaleStep,bottom),QPoint(i*scaleStep + left,leng + bottom));
    }

    painter.drawLine(left,bottom,left,top);

    // start
    _polygon[0] = QPoint(left,bottom);
    QPoint p2(0,bottom);
    for(uint16_t i=0; i<_points.size(); i++) {
        p2 = QPoint((_points[i].x())*step + left, bottom - static_cast<double>(h - 64)*(_points[i].y() / 255.0));
        _polygon[i+1] = (p2);
    }
    _polygon[ASCAN_SAMPLES_SIZE] = QPoint(right, p2.y());
    _polygon[ASCAN_SAMPLES_SIZE+1] = QPoint(right,bottom);
    // end

    painter.setPen(_ascanPen);
    painter.setBrush(_ascanBrush);
    painter.drawPolygon(_polygon.data(),_polygon.size());

    QPoint tvgStart(left,bottom);
    double tvgStep = width/200.0;
    painter.setPen(_tvgCurvePen);
    for(uint8_t i=0; i<_tvg.size(); i++) {
        QPoint tvgNext = QPoint((_tvg[i].x())*tvgStep + left, bottom - static_cast<double>(bottom)*(_tvg[i].y() / 127.0));
        painter.drawLine(tvgStart,tvgNext);
        tvgStart = tvgNext;
    }


    for(uint8_t i=0; i<_channels.size(); i++) {
        for(uint8_t j=0; j<_channels[i].gates().size(); j++) {
            Gate gate = _channels[i].gates()[j];
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

    quint64 time = _fpsTimer.restart();
    double fps = 1000.0 / time;
    painter.drawText(QPoint(w - 140, 30),"fps: " + QString::number(fps,'f', 2));
}

void AScanWidget::setChannelsInfo(std::vector<Channel> channels)
{
    _channels = channels;
    if(!channels.empty()) {
        onTVG(channels[0].generateTVG());
    }
    update();
}

void AScanWidget::onAScan(AScanDrawData *scan)
{
    if(isVisible()) {
        for(uint8_t j=0; j<_channels.size(); j++) {
            uint8_t chan = scan->_channel;
            if(chan == _channels[j].index()) {
                for(uint16_t i=0; i<scan->_samples.size(); i++) {
                    _points[i] = (QPoint(i,scan->_samples[i]));
                }
                _markerPos = scan->_markerPos;
                _markerValue = scan->_markerValue;
            }
        }

        //if(!_vsync)
        update();
    }
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

void AScanWidget::onTVG(TVG tvg)
{
    _tvg.clear();
    _tvg.reserve(TVG_SAMPLES_SIZE);

    for(int i=0; i<TVG_SAMPLES_SIZE; i++) {
        uint8_t sample = getTVGSample(tvg._samples,i);
        _tvg.push_back(QPoint(i,sample /2));
    }

    update();
}

void AScanWidget::onChannelChanged(Channel channel)
{
    for(uint8_t j=0; j<_channels.size(); j++) {
        uint8_t chan = channel.index();
        if(chan == _channels[j].index())
        {
            _channels[j] = channel;
            onTVG(channel.generateTVG());
        }
    }

    update();
}

