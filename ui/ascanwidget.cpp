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
        //painter.drawRect(100,100,500,500);
    int w = width();
    int h = height();
    double step = (w - 64)/800.0;
    QPoint center(32,h - 32);
    std::vector<QPoint> polygon;

    polygon.push_back(QPoint(center.x(),center.y()));
    for(int i=0; i<_points.size(); i++) {
        QPoint raw =_points.at(i);
        QPoint p2((raw.x())*step + center.x(), center.y() - static_cast<double>(center.y())*(raw.y() / 255.0));
        polygon.push_back(p2);
    }
    //polygon.push_back(QPoint(w - 32,center.y() - static_cast<double>(center.y())*(_points.at(_points.size()-1).y() / 255.0)));
    polygon.push_back(QPoint(w - 32,center.y()));
    //polygon.push_back(QPoint(0,h));
    painter.setPen(QPen(QColor(10,10,70), 2));

    painter.setBrush(QBrush(QColor(80,80,200)));

    painter.drawPolygon(polygon.data(),polygon.size());
}

void AScanWidget::onAScan(AScan scan)
{
    _points.clear();

    for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        _points.push_back(QPoint(i,scan._samples[i]));
    }
    update();
}

