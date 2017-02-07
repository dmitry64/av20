#include "ascanwidget.h"
#include "ui_ascanwidget.h"
#include <QPainter>
#include <QDebug>

AScanWidget::AScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanWidget)
{
    ui->setupUi(this);
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
    painter.fillRect(QRect(center,QPoint(w - 32, 32)),Qt::white);
    painter.drawRect(QRect(center,QPoint(w - 32, 32)));
    std::vector<QPoint> polygon;

    polygon.push_back(QPoint(center.x(),center.y()));
    QPoint p2(0,center.y());
    for(int i=0; i<_points.size(); i++) {
        QPoint raw =_points.at(i);
        p2 = QPoint((raw.x())*step + center.x(), center.y() - static_cast<double>(center.y() - 32)*(raw.y() / 255.0));
        polygon.push_back(p2);
    }
    polygon.push_back(QPoint(w - 32, p2.y()));
    polygon.push_back(QPoint(w - 32,center.y()));
    painter.setPen(QPen(QColor(10,10,70), 2));

    painter.setBrush(QBrush(QColor(80,80,200)));

    painter.drawPolygon(polygon.data(),polygon.size());

    QPoint tvgStart = center;
    double tvgStep = (w - 64)/200.0;
    painter.setPen(QPen(QColor(250,10,10), 2));
    for(int i=0; i<_tvg.size(); i++) {
        QPoint raw =_tvg.at(i);
        QPoint tvgNext = QPoint((raw.x())*tvgStep + center.x(), center.y() - static_cast<double>(center.y() - 32)*(raw.y() / 63.0));
        //qDebug() << (raw.x())*tvgStep + center.x();
        painter.drawLine(tvgStart,tvgNext);
        tvgStart = tvgNext;
    }

}

void AScanWidget::onAScan(AScan scan)
{
    _points.clear();
    _points.reserve(ASCAN_SAMPLES_SIZE);

    for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        _points.push_back(QPoint(i,scan._samples[i]));
    }
    update();
}


uint8_t getBitFromByteArray(uint8_t * ptr, int bit) {
    int b = bit / 8;
    return (ptr[b] >> (bit % 8)) & 0b00000001;
}

uint8_t getTVGSample(uint8_t * ptr, int sampleNum) {
    int bit = sampleNum * 6;
    uint8_t res = 0x00;
    res |= getBitFromByteArray(ptr,bit);
    res |= getBitFromByteArray(ptr,bit+1) << 1;
    res |= getBitFromByteArray(ptr,bit+2) << 2;
    res |= getBitFromByteArray(ptr,bit+3) << 3;
    res |= getBitFromByteArray(ptr,bit+4) << 4;
    res |= getBitFromByteArray(ptr,bit+5) << 5;
    return res;
}

void AScanWidget::onTVG(TVG tvg)
{
    _tvg.clear();
    _tvg.reserve(TVG_SAMPLES_SIZE);

    for(int i=0; i<TVG_SAMPLES_SIZE; i++) {
        uint8_t sample = getTVGSample(tvg._samples,i);
        _tvg.push_back(QPoint(i,sample));
    }

    update();
}
