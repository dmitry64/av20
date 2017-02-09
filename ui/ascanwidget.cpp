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
}

AScanWidget::~AScanWidget()
{
    delete ui;
}

void AScanWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //if(_ready.load()) {

    int w = width();
    int h = height();
    double step = (w - 64)/800.0;
    QPoint center(32,h - 32);
    painter.setPen(Qt::black);
    painter.fillRect(QRect(center,QPoint(w - 32, 0)),Qt::white);
    painter.drawRect(QRect(center,QPoint(w - 32, 0)));

    painter.fillRect(QRect(QPoint(0,center.y()),QPoint(w, w - 24)),Qt::white);
    double scaleStep = (w - 64)/200.0;
    for(int i=0; i<201; i++) {
        int leng = 0;
        if(i%10 == 0) {
            leng = 16;
            painter.drawText(center+QPoint(i*scaleStep+2,24),QString::number(i));
        } else {
            leng = 8;
        }
        painter.drawLine(center+QPoint(i*scaleStep,0),center+QPoint(i*scaleStep,leng));

    }



    _polygon[0] = (QPoint(center.x(),center.y()));
    QPoint p2(0,center.y());
    for(int i=0; i<_points.size(); i++) {
        QPoint raw =_points.at(i);
        p2 = QPoint((raw.x())*step + center.x(), center.y() - static_cast<double>(center.y())*(raw.y() / 255.0));
        _polygon[i+1] = (p2);
    }
    _polygon[ASCAN_SAMPLES_SIZE] = (QPoint(w - 32, p2.y()));
    _polygon[ASCAN_SAMPLES_SIZE+1] = (QPoint(w - 32,center.y()));
    painter.setPen(QPen(QColor(10,10,70), 2));

    painter.setBrush(QBrush(QColor(80,80,200)));

    painter.drawPolygon(_polygon.data(),_polygon.size());

    QPoint tvgStart = center;
    double tvgStep = (w - 64)/200.0;
    painter.setPen(QPen(QColor(250,10,10), 2));
    for(int i=0; i<_tvg.size(); i++) {
        QPoint raw =_tvg.at(i);
        QPoint tvgNext = QPoint((raw.x())*tvgStep + center.x(), center.y() - static_cast<double>(center.y() )*(raw.y() / 127.0));
        //qDebug() << (raw.x())*tvgStep + center.x();
        painter.drawLine(tvgStart,tvgNext);
        tvgStart = tvgNext;
    }

    quint64 time = _fpsTimer.restart();
    double fps = 1000.0 / time;
    painter.drawText(QPoint(w - 140, 30),"fps: " + QString::number(fps,'f', 2));
}

void AScanWidget::onAScan(AScan scan)
{

    for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        _points[i] = (QPoint(i,scan._samples[i]));
    }
    update();
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

