#include "bscanwidget.h"
#include "ui_bscanwidget.h"
#include <QPainter>
#include <QLinearGradient>
#include <QDebug>

void BScanWidget::setChannelsInfo(std::vector<ChannelsInfo> selectedChannels)
{
    _samplesArray.clear();
    for(size_t i=0; i<selectedChannels.size(); i++) {
        std::pair< ChannelsInfo, BScanDrawArray > pair;
        pair.first = selectedChannels.at(i);
        _samplesArray.push_back(pair);
    }
    //reset();
}

void BScanWidget::setActiveChannelData(const Channel & channel, ChannelsInfo info)
{
    _channelData = channel;
    _info = info;
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

    _info._channel = 0;
    _info._displayChannel = 0;

    reset();

    //for(uint8_t i=0; i<MAX_CHANNELS_COUNT; i++) {
    //   _samplesMap[i] = std::map< DisplayChannelID, BScanDrawArray >();

    //std::pair< std::vector< std::vector<BScanDrawSample> > , uint8_t> pair;
    //pair.first.resize(_width);
    //pair.second = 0;
    //_samples.push_back(pair);
    //}

    _restrictedToChannel = false;
    _end = _width - 1;
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
    const ChannelID chan = _channelData.index();
    const uint16_t elements = 0;//std::max(static_cast<int>(_width - _samplesArray._index),0);

    int index = -1;
    for(size_t i=0; i<_samplesArray.size(); i++) {
        if(_samplesArray[i].first._channel == _info._channel && _samplesArray[i].first._displayChannel == _info._displayChannel) {
            index = i;
            break;
        }
    }

    if(index != -1) {

        uint16_t k = _samplesArray[index].second._index;


        for(uint16_t i=elements; i<_width; i++) {
            const std::vector<BScanDrawSample> & sam = (_samplesArray[index].second._samples)[k];
            const uint8_t samplesCount = sam.size();
            if(k == _end ) {
                k = 0;
            }
            else {
                k++;
            }

            for(uint16_t y=0; y<samplesCount; y++) {
                const BScanDrawSample & sample = sam[y];
                const double y1 = sample._begin * hstep;
                const double y2 = sample._end * hstep;
                painter.fillRect(QRectF(static_cast<double>(left) + step*i,1.0 + y1, step, y2 - y1), getColorByLevel(sample._level));
            }
        }

        const std::vector<Gate> & gates = _channelData.getDisplayChannels().at(_info._displayChannel).gates();

        for(size_t i=0; i<gates.size(); i++) {
            const Gate & gate = gates[i];
            const uint16_t y1 = static_cast<double>(gate._start) * hstep;
            const uint16_t y2 = static_cast<double>(gate._finish) * hstep;
            uint16_t offset = w - 32 + ((gate._level/255.0) *32) + 1;
            painter.setPen(QPen(getColorByLevel(gate._level),2));
            painter.drawLine(offset,y1,offset,y2);
        }
    }
    //}
}

void BScanWidget::setRestrictedToChannel(bool flag)
{
    _restrictedToChannel = flag;
}

void BScanWidget::reset()
{
    _samplesArray.clear();
}

void BScanWidget::onBScan(BScanDrawData *scan)
{
    ChannelsInfo info = scan->_info;
    if(_restrictedToChannel) {
        if(info._channel != _info._channel || info._displayChannel != _info._displayChannel) {
            return;
        }
    }
    for(size_t i=0; i<_samplesArray.size(); i++) {
        if(_samplesArray[i].first._channel == info._channel && _samplesArray[i].first._displayChannel == info._displayChannel) {
            int oldStart = _samplesArray[i].second._index;
            _samplesArray[i].second._samples[oldStart] = scan->_samples;
            _samplesArray[i].second._index++;

            if(_samplesArray[i].second._index == _width) {
                _samplesArray[i].second._index = 0;
            }
        }
    }

    if(isVisible()) {
        update();
    }
}

void BScanWidget::onChannelChanged(Channel channel)
{
    if(_channelData.index() == channel.index()) {
        _channelData = channel;
    }
    update();
}
