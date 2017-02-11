#include "bscanwidget.h"
#include "ui_bscanwidget.h"
#include <QPainter>
#include <QLinearGradient>
#include <QDebug>

std::vector<Channel> BScanWidget::channels() const
{
    return _channels;
}

bool BScanWidget::channelSelected(uint8_t chan)
{
    for(int i=0; i<_channels.size(); i++) {
        if(_channels[i].index() == chan) {
            return true;
        }
    }
    return false;
}

BScanWidget::BScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanWidget)
{
    ui->setupUi(this);
    _width = 100;

    for(int i=0; i<MAX_CHANNELS_COUNT; i++) {
        std::pair< std::vector<BScanDrawData> , int> pair;
        for(int j=0; j<_width; j++) {
            BScanDrawData data;
            data._channel = j;
            data._samples.resize(ASCAN_SAMPLES_SIZE);
            pair.first.push_back(data);
        }
        //pair.first.resize(_width);
        //memset(pair.first.data(),0x00,pair.first.size());
        pair.second = 0;
        _scans.push_back(pair);
    }

    _end = 99;
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
    QPoint center(32,h-1);

    painter.fillRect(QRect(QPoint(center.x() - 32,0),QPoint(32,center.y())),Qt::white);
    painter.fillRect(QRect(QPoint(w - 32,0),QPoint(w,center.y())),Qt::white);

    painter.fillRect(QRect(QPoint(center.x(),0),QPoint(w - 32,center.y())),Qt::white);
    painter.drawRect(QRect(QPoint(center.x(),0),QPoint(w - 32 - 1,center.y()-1)));
    painter.drawRect(QRect(QPoint(0,0),QPoint(w - 2,center.y()-1)));

    /*
    double scaleStep = (h - 4)/10.0;
    for(int i=0; i<10; i++) {
        painter.drawLine(QPoint(16,i*scaleStep),QPoint(32,i*scaleStep));
        //painter.drawText(QPoint(1,i*scaleStep + 16),QString::number(i*20));
    }
    */

    int samples = _width;
    double step = static_cast<double>(w - 64.0) / static_cast<double>(samples);

    for(uint8_t n=0; n<_channels.size(); n++) {
        int y = _channels[n].index();
        int elements = std::max(static_cast<int>(samples - _scans[y].first.size()),0);
        int k = (_scans[y]).second;

        for(uint16_t i=elements; i<samples; i++) {
            QLinearGradient grad(0,0,0,1);
            grad.setCoordinateMode(QGradient::ObjectBoundingMode);
            //int grstep = 800.0 / center.y();
            int grstep = 5;
            BScanDrawData * data = &(((_scans[y]).first)[k]);
            for(uint16_t j=0; j<data->_samples.size(); j+=grstep) {
                int sam = data->_samples[j];
                if(y%2) {
                    grad.setColorAt(j / 800.0, QColor(sam,10,10, sam));
                } else {
                    grad.setColorAt(j / 800.0, QColor(10,10,sam, sam));
                }
            }
            if(k == _end ) {
                k = 0;
            } else {
                k++;
            }

            painter.fillRect(QRectF(QPointF(32.0 + step*i, center.y()),QPointF(32.0 + step*(i+1),0)), grad);
        }
    }


    /*for(int i=_scans.size() -1; i>=0; i--) {
        QLinearGradient grad(0,0,0,h - 4);
        for(int j=0; j<ASCAN_SAMPLES_SIZE; j+=5) {
            int sam = _scans[i]._samples[j];
            grad.setColorAt(static_cast<double>(j) / 800.0, QColor(sam,10,255 - sam));
        }
        QPoint offset(i,0);
        painter.fillRect(QRect(QPoint(w - 32, 0) -offset,QPoint(w - 32, center.y())-offset),grad);
    }*/
}

void BScanWidget::setChannelsInfo(std::vector<Channel> channels)
{
    _channels = channels;
}

void BScanWidget::onBScan(BScanDrawData *scan)
{
    //_scans.push_back(scan);
    uint8_t chan = scan->_channel;
    //qDebug() << _channels.size();
    //if(channelSelected(chan)) {
        int oldStart = (_scans[chan]).second;
        memcpy((((_scans[chan]).first)[oldStart])._samples.data(), scan->_samples.data(),ASCAN_SAMPLES_SIZE);
        // = scan;
        (_scans[chan]).second++;
        if((_scans[chan]).second == _width) {
            (_scans[chan]).second = 0;
        }


    //}
    if(isVisible()) {
        update();
    }
}
