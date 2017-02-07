#include "ascanwidget.h"
#include "ui_ascanwidget.h"
#include <QPainter>
#include <QDebug>

AScanWidget::AScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanWidget),
    _ascanSource(0)
{
    ui->setupUi(this);
    _ready.store(false);
}

AScanWidget::~AScanWidget()
{
    delete ui;
}

void AScanWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(_ready.load()) {
        //painter.drawRect(100,100,500,500);
        int w = width();
        int h = height();
        double step = w/800.0;
        QPoint p1 (0,0);

        for(int i=0; i<800; i++) {
            uint8_t sample = _ascanSource[i];
            qDebug() << "S:" << sample;
            //qDebug() << "Val = " << reinterpret_cast<unsigned char>(sample);
            //int y = static_cast<double>(h) - qRound(static_cast<double>(h) * 2 * static_cast<unsigned int>(sample));
            //int y = sample;
            QPoint p2((i+1)*step,h - static_cast<double>(h)*(sample / 255.0));
            painter.drawLine(p1,p2);
            p1 = p2;
        }
    }

    update();
}

void AScanWidget::setSource(uint8_t *ptr)
{
    qDebug() << "set source!";
    _ascanSource = ptr;
    _ready.store(true);
}
