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
}

AScanWidget::~AScanWidget()
{
    delete ui;
}

void AScanWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int w = width();
    int h = height();
    int width = w - 64;
    double step = width/800.0;
    QPoint bottomLeft(32,h - 32);
    QPoint topRight(w - 32, 0);

    painter.setPen(Qt::black);
    painter.fillRect(QRect(bottomLeft,topRight),Qt::white);
    painter.drawRect(QRect(bottomLeft,topRight));

    painter.fillRect(QRect(QPoint(0,bottomLeft.y()),QPoint(w, w - 24)),Qt::white);
    int scale = 200;
    double scaleStep = width/static_cast<double>(scale);
    for(uint8_t i=0; i<scale+1; i++) {
        int leng = 0;
        if(i%10 == 0) {
            leng = 16;
            if(i!=scale) {
                painter.drawText(bottomLeft+QPoint(i*scaleStep+2,24),QString::number(i));
            }
        } else {
            leng = 8;
        }
        painter.drawLine(bottomLeft+QPoint(i*scaleStep,0),bottomLeft+QPoint(i*scaleStep,leng));

    }

    _polygon[0] = (QPoint(bottomLeft.x(),bottomLeft.y()));
    QPoint p2(0,bottomLeft.y());
    for(uint16_t i=0; i<_points.size(); i++) {
        QPoint raw =_points.at(i);
        p2 = QPoint((raw.x())*step + bottomLeft.x(), bottomLeft.y() - static_cast<double>(bottomLeft.y())*(raw.y() / 255.0));
        _polygon[i+1] = (p2);
    }
    _polygon[ASCAN_SAMPLES_SIZE] = (QPoint(topRight.x(), p2.y()));
    _polygon[ASCAN_SAMPLES_SIZE+1] = (QPoint(topRight.x(),bottomLeft.y()));
    painter.setPen(_ascanPen);
    painter.setBrush(_ascanBrush);
    painter.drawPolygon(_polygon.data(),_polygon.size());

    QPoint tvgStart = bottomLeft;
    double tvgStep = width/200.0;
    painter.setPen(_tvgCurvePen);
    for(uint8_t i=0; i<_tvg.size(); i++) {
        QPoint raw =_tvg.at(i);
        QPoint tvgNext = QPoint((raw.x())*tvgStep + bottomLeft.x(), bottomLeft.y() - static_cast<double>(bottomLeft.y() )*(raw.y() / 127.0));
        painter.drawLine(tvgStart,tvgNext);
        tvgStart = tvgNext;
    }

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
}

void AScanWidget::onAScan(AScanDrawData *scan)
{
    if(isVisible()) {
        for(int j=0; j<_channels.size(); j++) {
            uint8_t chan = scan->_channel;
            if(chan == _channels[j].index()) {
                for(int i=0; i<scan->_samples.size(); i++) {
                    _points[i] = (QPoint(i,scan->_samples[i]));
                }
            }
        }
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

