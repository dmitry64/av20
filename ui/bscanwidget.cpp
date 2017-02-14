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
    _width = 1000;

    for(int i=0; i<MAX_CHANNELS_COUNT; i++) {
        std::pair< std::vector< std::vector<BScanDrawSample> > , int> pair;
        pair.first.resize(_width);
        pair.second = 0;
        _samples.push_back(pair);
    }

    _restrictedToChannel = false;
    //this->setAttribute(Qt::WA_OpaquePaintEvent);

    _end = 999;
}

BScanWidget::~BScanWidget()
{
    delete ui;
}

void BScanWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const int w = width();
    const int h = height();
    painter.setPen(Qt::black);

    const int bottom = h -1;
    const int left = 32;

    painter.fillRect(0,0,32,bottom,Qt::white);
    painter.fillRect(w - 32,0,w,bottom,Qt::white);
    painter.fillRect(left,0,w - 32,bottom,Qt::white);
    painter.drawRect(left,0,w - 32 - 1,bottom-1);
    painter.drawRect(0,0,w - 32,bottom-1);

    /*
    double scaleStep = (h - 4)/10.0;
    for(int i=0; i<10; i++) {
        painter.drawLine(QPoint(16,i*scaleStep),QPoint(32,i*scaleStep));
        //painter.drawText(QPoint(1,i*scaleStep + 16),QString::number(i*20));
    }
    */


    double step = (w - 64) / static_cast<double>(_width);

    for(uint8_t n=0; n<_channels.size(); n++) {
        uint8_t chan = _channels[n].index();
        uint16_t elements = std::max(static_cast<int>(_width - _samples[chan].first.size()),0);
        uint16_t k = (_samples[chan]).second;


        for(uint16_t i=elements; i<_width; i++) {
            std::vector<BScanDrawSample> sam = ((_samples[chan]).first)[k];
            if(k == _end ) {
                k = 0;
            } else {
                k++;
            }

            //painter.fillRect(QRectF(left + step*i,1.0,step,bottom-2.0), Qt::white);

            for(int y=0; y<sam.size(); y++) {
                int y1 = (sam[y]._begin) * ( h / 200.0);
                int y2 = (sam[y]._end) * ( h / 200.0);
                uint8_t level = sam[y]._level;
                painter.fillRect(QRectF(left + step*i,1.0 + y1,step, y2 - y1), QColor( level ,255 - level, 0 ));
            }
        }

        std::vector<Gate> gates = _channels[n].gates();

        for(uint8_t i=0; i<gates.size(); i++) {
            int y1 = (gates[i]._start) * ( h / 200.0);
            int y2 = (gates[i]._finish) * ( h / 200.0);
            uint16_t level = gates[i]._level;
            uint16_t offset = w - 32 + ((level/255.0) *32) + 1;
            painter.setPen(QPen(QColor( level ,255 - level, 0 ),2));
            painter.drawLine(offset,y1,offset,y2);
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

void BScanWidget::setRestrictedToChannel(bool flag)
{
    _restrictedToChannel = flag;
}

void BScanWidget::onBScan(BScanDrawData *scan)
{
    uint8_t chan = scan->_channel;
    if(_restrictedToChannel) {
        if(!channelSelected(chan)) {
            return;
        }
    }

    int oldStart = (_samples[chan]).second;

    ((_samples[chan]).first)[oldStart] = scan->_samples;

    (_samples[chan]).second++;

    if((_samples[chan]).second == _width) {
        (_samples[chan]).second = 0;
    }

    /*QLinearGradient grad(0,0,0,1);
    grad.setCoordinateMode(QGradient::ObjectBoundingMode);

    for(uint16_t j=0; j<scan->_samples.size(); j+=8) {
        uint8_t sam = scan->_samples[j];
        if(chan%2) {
            grad.setColorAt(j / 800.0, QColor(sam,10,10, sam));
        } else {
            grad.setColorAt(j / 800.0, QColor(10,10,sam, sam));
        }
    }

    (_gradients[chan].first)[oldStart] = grad;
    (_gradients[chan]).second++;

    if((_gradients[chan]).second == _width) {
        (_gradients[chan]).second = 0;
    }*/

    if(isVisible()) {
        update();
    }
}

void BScanWidget::onChannelChanged(Channel channel)
{
    for(uint8_t j=0; j<_channels.size(); j++) {
        uint8_t chan = channel.index();
        if(chan == _channels[j].index())
        {
            _channels[j] = channel;
        }
    }
}
