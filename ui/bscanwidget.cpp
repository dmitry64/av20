#include "bscanwidget.h"
#include "ui_bscanwidget.h"
#include <QPainter>


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




}
