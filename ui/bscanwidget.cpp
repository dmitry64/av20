#include "bscanwidget.h"
#include "ui_bscanwidget.h"
#include <QPainter>
#include <QLinearGradient>
#include <QDebug>

std::vector<Channel*> BScanWidget::channels() const
{
    return _channels;
}

bool BScanWidget::channelSelected(uint8_t chan)
{
    for(int i=0; i<_channels.size(); i++) {
        if(_channels[i]->index() == chan) {
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
    _width = 800;

    for(int i=0; i<MAX_CHANNELS_COUNT; i++) {
        std::pair< std::vector< std::vector<BScanDrawSample> > , int> pair;
        pair.first.resize(_width);
        pair.second = 0;
        _samples.push_back(pair);
    }

    _restrictedToChannel = false;
    //this->setAttribute(Qt::WA_OpaquePaintEvent);

    _end = 799;
}

BScanWidget::~BScanWidget()
{
    for(size_t i=0; i<_channels.size(); i++) {
        delete _channels[i];
    }
    _channels.clear();
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

    double step = (w - 64) / static_cast<double>(_width);
    double hstep = ( h / 200.0);

    for(uint8_t n=0; n<_channels.size(); n++) {
        uint8_t chan = _channels[n]->index();
        uint16_t elements = std::max(static_cast<int>(_width - _samples[chan].first.size()),0);
        uint16_t k = (_samples[chan]).second;


        for(uint16_t i=elements; i<_width; i++) {
            std::vector<BScanDrawSample> sam = ((_samples[chan]).first)[k];
            if(k == _end ) {
                k = 0;
            } else {
                k++;
            }

            for(uint16_t y=0; y<sam.size(); y++) {
                uint16_t y1 = (sam[y]._begin) * hstep;
                uint16_t y2 = (sam[y]._end) * hstep;
                uint8_t level = sam[y]._level;
                painter.fillRect(QRectF(left + step*i,1 + y1,step, y2 - y1), QColor( level ,255 - level, 0 ));
            }
        }

        std::vector<Gate> gates = _channels.at(n)->rx()->gates();

        for(size_t i=0; i<gates.size(); i++) {
            uint16_t y1 = (gates[i]._start) * hstep;
            uint16_t y2 = (gates[i]._finish) * hstep;
            uint16_t level = gates[i]._level;
            uint16_t offset = w - 32 + ((level/255.0) *32) + 1;
            painter.setPen(QPen(QColor( level ,255 - level, 0 ),2));
            painter.drawLine(offset,y1,offset,y2);
        }
    }
}

void BScanWidget::setChannelsInfo(std::vector<Channel*> channels)
{
    for(size_t i=0; i<_channels.size(); i++) {
        delete _channels.at(i);
    }
    _channels.clear();
    std::vector<Channel*> result;
    for(size_t i=0; i<channels.size(); i++) {
        result.push_back(new Channel(channels.at(i)));
    }
    _channels = result;
}

void BScanWidget::setRestrictedToChannel(bool flag)
{
    _restrictedToChannel = flag;
}

void BScanWidget::reset()
{
    for(size_t i=0; i<_channels.size(); i++) {
        delete _channels.at(i);
    }
    _channels.clear();
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

    if(isVisible()) {
        update();
    }
}

void BScanWidget::onChannelChanged(Channel * channel)
{
    for(uint8_t j=0; j<_channels.size(); j++) {
        uint8_t chan = channel->index();
        if(chan == _channels[j]->index())
        {
            delete _channels[j];
            _channels[j] = new Channel(channel);
        }
    }
}
