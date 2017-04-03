#include "bscanwidget.h"
#include "ui_bscanwidget.h"
#include <QPainter>
#include <QLinearGradient>
#include <QDebug>

void BScanWidget::setChannelsInfo(const std::vector<ChannelsInfo> & selectedChannels)
{
    _samplesArray.clear();

    for(auto it=selectedChannels.begin(); it!=selectedChannels.end(); it++) {
        std::pair< ChannelsInfo, BScanDrawArray > pair;
        pair.first = it.operator*();
        _samplesArray.push_back(pair);
    }
}

void BScanWidget::setActiveChannelData(const Channel & channel, const ChannelsInfo & info)
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
    _width = 650;

    _info._channel = 0;
    _info._displayChannel = 0;

    reset();

    _restrictedToChannel = false;
    _end = _width - 1;
}

BScanWidget::~BScanWidget()
{
    delete ui;
}

void BScanWidget::drawGates(const double hstep, QPainter & painter, const int right)
{
    const std::vector<Gate> &gates = _channelData.getDisplayChannels().at(_info._displayChannel).gates();

    for(auto it=gates.begin(); it!=gates.end(); it++) {
        const Gate &gate = it.operator*();
        const uint16_t y1 = static_cast<double>(gate._start) * hstep;
        const uint16_t y2 = static_cast<double>(gate._finish) * hstep;
        uint16_t offset = right + ((gate._level/255.0) *32) + 1;
        painter.setPen(QPen(getColorByLevel(gate._level),2));
        painter.drawLine(offset,y1,offset,y2);
    }
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
    const int right = w - 32;

    const QPalette & pal = this->palette();
    QColor bgColor = pal.color(QPalette::Window);
    bgColor = bgColor.lighter(170.0f);

    painter.fillRect(0,0,32,bottom,bgColor);
    painter.fillRect(right,0,w,bottom,bgColor);
    painter.fillRect(left,0,right,bottom,bgColor);
    painter.drawRect(left,0,right - 1,bottom-1);
    painter.drawRect(0,0,right,bottom-1);

    const double step = (w - 64) / static_cast<double>(_width);
    const double hstep = ((h - 1.0) / 200.0);

    const uint16_t elements = 0;

    int index = -1;
    int curIndex = 0;
    for(auto it=_samplesArray.begin(); it!=_samplesArray.end(); it++) {
        const ChannelsInfo & curInfo = it.operator*().first;
        if(curInfo._channel == _info._channel && curInfo._displayChannel == _info._displayChannel) {
            index = curIndex;
            break;
        }
        curIndex++;
    }

    if(index != -1) {
        const BScanDrawArray & curArray = _samplesArray[index].second;
        uint16_t k = curArray._index;

        for(uint16_t i=elements; i<_width; i++) {
            const std::vector<BScanDrawSample> & sam = (curArray._samples)[k];
            if(k == _end ) {
                k = 0;
            }
            else {
                k++;
            }
            double stepOffset = static_cast<double>(left) + step*i;

            for(auto it=sam.begin(); it!=sam.end(); it++) {
                const BScanDrawSample & sample = it.operator*();
                const double y1 = sample._begin * hstep;
                const double y2 = sample._end * hstep;
                painter.fillRect(QRectF(stepOffset,1.0 + y1, step, y2 - y1), getColorByLevel(sample._level));
            }
        }

        drawGates(hstep, painter, right);
    }
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
    Q_ASSERT(scan);
    ChannelsInfo info = scan->_info;
    if(_restrictedToChannel) {
        if(info._channel != _info._channel || info._displayChannel != _info._displayChannel) {
            return;
        }
    }
    for(auto it=_samplesArray.begin(); it!=_samplesArray.end(); it++) {
        const ChannelsInfo & curInfo = it.operator*().first;
        BScanDrawArray & curArray = it.operator*().second;
        if(curInfo._channel == info._channel && curInfo._displayChannel == info._displayChannel) {
            int oldStart = curArray._index;
            curArray._samples[oldStart] = scan->_samples;
            curArray._index++;

            if(curArray._index == _width) {
                curArray._index = 0;
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
