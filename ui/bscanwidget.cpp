#include "bscanwidget.h"
#include "ui_bscanwidget.h"
#include <QPainter>
#include <QDebug>

BScanWidget::BScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanWidget)
{
    ui->setupUi(this);
}

BScanWidget::~BScanWidget()
{
    delete ui;
}

void BScanWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int w = width();
    int h = height();
    painter.setPen(Qt::black);
    QPoint center(32,h - 4);

    painter.fillRect(QRect(QPoint(center.x() - 32,0),QPoint(32,center.y())),Qt::white);
    painter.fillRect(QRect(QPoint(w - 32,0),QPoint(w,center.y())),Qt::white);

    painter.fillRect(QRect(QPoint(center.x(),0),QPoint(w - 32,center.y())),Qt::white);
    painter.drawRect(QRect(QPoint(center.x(),0),QPoint(w - 32,center.y())));

    double scaleStep = (h - 4)/10.0;
    for(int i=0; i<10; i++) {
        painter.drawLine(QPoint(16,i*scaleStep),QPoint(32,i*scaleStep));
        painter.drawText(QPoint(1,i*scaleStep + 16),QString::number(i*20));
    }



    for(int i=0; i<_scans.size(); i++) {
        QLinearGradient grad;

        for(int j=0; j<ASCAN_SAMPLES_SIZE; j++) {
            int sam = _scans[i]._samples[j];
            grad.setColorAt(static_cast<double>(j) / 800.0,QColor(sam * 10,10,10));
        }
        painter.setBrush(QBrush(grad));
        QPoint offset(i*2,0);
        painter.drawRect(QRect(QPoint(w - 32, 0) -offset,QPoint(w - 32, center.y())-offset));
    }
}

void BScanWidget::onAScan(AScan scan)
{
    _scans.push_back(scan);
    /*for(int i=0; i<ASCAN_SAMPLES_SIZE; i++) {
        //_points[i] = (QPoint(i,scan._samples[i]));
    }*/
    update();
}
