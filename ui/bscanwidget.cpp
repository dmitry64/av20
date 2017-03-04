#include "bscanwidget.h"
#include "ui_bscanwidget.h"
#include <QPainter>
#include <QLinearGradient>
#include <QDebug>

void BScanWidget::setChannelInfo(const Channel &channel, DisplayChannelID dispChannelId)
{
    _channelData = channel;
    _displayChannelId = dispChannelId;
}

Channel BScanWidget::channelData() const
{
    return _channelData;
}

BScanWidget::BScanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanWidget)
{
    ui->setupUi(this);
    _width = 800;

    _displayChannelId = 0;

    for(int i=0; i<MAX_CHANNELS_COUNT; i++) {
        std::pair< std::vector< std::vector<BScanDrawSample> > , int> pair;
        pair.first.resize(_width);
        pair.second = 0;
        _samples.push_back(pair);
    }

    _restrictedToChannel = false;

    _end = 799;
}

BScanWidget::~BScanWidget()
{

}

void BScanWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
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

    const double step = (w - 64) / static_cast<double>(_width);
    const double hstep = ((h - 1.0) / 200.0);

    // uint8_t channelsCount = _channels.size();

    //for(uint8_t n=0; n<channelsCount; n++) {
    const uint8_t chan = _channelData.index();
    const uint16_t elements = std::max(static_cast<int>(_width - _samples[chan].first.size()),0);
    uint16_t k = (_samples[chan]).second;


    for(uint16_t i=elements; i<_width; i++) {
        const std::vector<BScanDrawSample> & sam = ((_samples[chan]).first)[k];
        const uint8_t samplesCount = sam.size();
        if(k == _end ) {
            k = 0;
        }
        else {
            k++;
        }

        for(uint16_t y=0; y<samplesCount; y++) {
            const BScanDrawSample & sample = sam[y];
            const double y1 = static_cast<double>(sample._begin) * hstep;
            const double y2 = static_cast<double>(sample._end) * hstep;
            painter.fillRect(QRectF(static_cast<double>(left) + step*i,1.0 + y1, step, y2 - y1), getColorByLevel(sample._level));
        }
    }

    /*const std::vector<Gate> & gates = _channels.at(n)->rx()->gates();

    for(size_t i=0; i<gates.size(); i++) {
        const Gate & gate = gates[i];
        const uint16_t y1 = static_cast<double>(gate._start) * hstep;
        const uint16_t y2 = static_cast<double>(gate._finish) * hstep;
        uint16_t offset = w - 32 + ((gate._level/255.0) *32) + 1;
        painter.setPen(QPen(getColorByLevel(gate._level),2));
        painter.drawLine(offset,y1,offset,y2);
    }*/
    //}
}

void BScanWidget::setRestrictedToChannel(bool flag)
{
    _restrictedToChannel = flag;
}

void BScanWidget::reset()
{

}

void BScanWidget::onBScan(BScanDrawData *scan)
{
    uint8_t chan = scan->_channel;
    if(_restrictedToChannel) {
        if(chan!=_channelData.index()) {
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

void BScanWidget::onChannelChanged(Channel channel)
{
    /*Q_ASSERT(channel);
    for(uint8_t j=0; j<_channels.size(); j++) {
        uint8_t chan = channel->index();
        if(chan == _channels[j]->index()) {
            Channel * chan = _channels[j];
            Q_ASSERT(chan);
            delete chan;
            _channels[j] = new Channel(channel);
        }
    }
    update();*/
}
