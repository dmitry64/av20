#include "ascanplot.h"
#include <QPainter>

void AScanPlot::setTvgCurve(const TVGCurve *curve)
{
    _tvgSamples.clear();
    for(int i=0; i<200; i++) {
        double val = curve->getSample(i/200.0);
        _tvgSamples.push_back(val);
    }
    _tvgReferencePoints = curve->getReferencePoints();
}

void AScanPlot::reset()
{

}

void AScanPlot::setBgColor(const QColor &bgColor)
{
    _bgColor = bgColor;
}

void AScanPlot::setAScanColor(const QColor &ascanColor)
{
    _ascanBrush.setColor(ascanColor);
}

void AScanPlot::setScale(const uint16_t &scale)
{
    _scale = scale;
}

void AScanPlot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);

    int h = height();
    int w = width();
    painter.fillRect(0,0,w,h,_bgColor);
    drawAscan(painter,w,h);
    drawGates(painter,w,h);
    drawTvgCurve(painter,w,h);
    drawMarker(painter,w,h);
    if(_drawFPS) {
        drawFps(painter,w - 100, 16);
    }
}

AScanPlot::AScanPlot(QWidget *parent) : QWidget(parent)
{
    _fpsTimer.restart();
    _polygon.resize(ASCAN_SAMPLES_SIZE+2);
    _ascanBrush = QBrush(QColor(80,80,200));
    _ascanPen = QPen(QColor(10,10,70), 1);
    _tvgCurvePen = QPen(QColor(250,10,10), 2);
    _tvgCurvePen.setCapStyle(Qt::RoundCap);
    _markerPos = 0;
    _markerValue = 0;
    _bgColor = this->palette().color(QPalette::Window);
    _scale = 200;
    _displayChannelId = 0;
    _drawFPS = false;
}

AScanPlot::~AScanPlot()
{

}

void AScanPlot::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
}

void AScanPlot::drawAscan(QPainter &painter, int width, int height)
{
    painter.setPen(_ascanPen);
    painter.setBrush(_ascanBrush);

    const double step = width/800.0;
    uint16_t size = _samples.size();
    uint16_t currentCount = 0;
    for(uint16_t i=0; i<size; i++) {
        if(_samples[i] > 0) {
            if(currentCount==0) {
                _polygon[currentCount] = QPoint((i-1)*step, height);
                currentCount++;
            }
            _polygon[currentCount] = QPoint(i*step, height - height*(_samples[i] / 256.0));
            currentCount++;
        }
        else {
            if(currentCount!=0) {
                _polygon[currentCount] = QPoint( (i+1)*step, height);
                currentCount++;
                painter.drawPolygon(_polygon.data(),currentCount, Qt::FillRule::OddEvenFill);
                currentCount = 0;
            }
        }
    }
    if(currentCount!=0) {
        _polygon[currentCount] = QPoint(800*step,height - height*(_samples[size-1] / 256.0));
        currentCount++;
        painter.drawPolygon(_polygon.data(),currentCount, Qt::FillRule::OddEvenFill);
    }
}

void AScanPlot::drawTvgCurve(QPainter &painter,int width, int height)
{
    if(!_tvgSamples.empty()) {
        double tvgStep = width/200.0;
        QPoint tvgStart(0, height - _tvgSamples.at(0) *height);
        int i=0;
        painter.setPen(_tvgCurvePen);
        for(auto it=_tvgSamples.begin(); it!=_tvgSamples.end(); it++) {
            int x = i*tvgStep;
            int y = height - it.operator*() * (height) ;
            QPoint tvgNext = QPoint(x,y);
            painter.drawLine(tvgStart,tvgNext);
            tvgStart = tvgNext;
            i++;
        }
        painter.setPen(Qt::black);
        painter.setBrush(QBrush(Qt::green));
        for(auto it=_tvgReferencePoints.begin(); it!=_tvgReferencePoints.end(); it++) {
            const std::pair<double,double> & pair = it.operator*();
            QPoint p(pair.first * width ,height - pair.second * (height));
            painter.drawEllipse(QRect(p-QPoint(3,3),p+QPoint(3,3)));
        }
    }
}

void AScanPlot::drawMarker(QPainter &painter, int width, int height)
{
    painter.setPen(QPen(Qt::black, 1, Qt::PenStyle::DotLine));
    int markerHeight = (height) -  (_markerValue / 255.0) * height ;
    int markerPos =  (_markerPos / 800.0) * width;
    painter.drawLine(0, markerHeight,markerPos, markerHeight);
    painter.drawLine(markerPos,markerHeight,markerPos,height);
    painter.setPen(Qt::red);
    painter.drawLine(markerPos,height,markerPos,height-16);
}

void AScanPlot::drawGates(QPainter &painter, int width, int height)
{
    double scaleStep = width/static_cast<double>(_scale);
    const auto & dispChans = _channelData.getDisplayChannels();
    const auto & gates = dispChans[_displayChannelId].gates();

    for(auto it=gates.begin(); it!=gates.end(); it++) {
        const Gate & gate = it.operator*();
        const int level = height - (gate._level * (height/255.0));
        QPen gatePen = QPen(getColorByLevel(gate._level),3);
        gatePen.setCapStyle(Qt::RoundCap);
        painter.setPen(gatePen);

        painter.drawLine(gate._start * scaleStep,level,gate._finish* scaleStep, level);
        painter.drawLine(gate._start * scaleStep,level,gate._start * scaleStep - 5, level + 5);
        painter.drawLine(gate._start * scaleStep,level,gate._start * scaleStep - 5, level - 5);
        painter.drawLine(gate._finish * scaleStep,level,gate._finish * scaleStep + 5, level + 5);
        painter.drawLine(gate._finish * scaleStep,level,gate._finish * scaleStep + 5, level - 5);
    }
}

void AScanPlot::drawFps(QPainter &painter, int posx, int posy)
{
    const quint64 time = _fpsTimer.nsecsElapsed();
    _fpsTimer.start();
    double fps = 1/(static_cast<double>(time) / 1000000000.0);
    painter.drawText(QPoint(posx, posy),"fps: " + QString::number(fps,'f', 3));
}

void AScanPlot::setChannelInfo(const Channel & channel, DisplayChannelID dispChannelId)
{
    _channelData = channel;
    _displayChannelId = dispChannelId;
    const auto & dispChans = channel.getDisplayChannels();
    const DisplayChannel & disp = dispChans[_displayChannelId];
    const RxChannel & rx = disp.getRx();
    const TVGCurve * tvg = rx.getTvgCurve();
    Q_ASSERT(tvg);
    setTvgCurve(tvg);
}

void AScanPlot::onAScan(const AScanDrawData & scan)
{
    if(isVisible()) {
        uint8_t chan = scan._channel;
        if(chan == _channelData.index()) {
            _samples = scan._samples;
            _markerPos = scan._markerPos;
            _markerValue = scan._markerValue;
        }
        update();
    }
}

void AScanPlot::onChannelChanged(const Channel & channel)
{
    if(_channelData.index() == channel.index()) {
        _channelData = channel;
        const auto & dispChannels = channel.getDisplayChannels();
        const DisplayChannel & disp = dispChannels.at(_displayChannelId);
        const RxChannel & rx = disp.getRx();
        const TVGCurve * tvg = rx.getTvgCurve();
        Q_ASSERT(tvg);
        setTvgCurve(tvg);
    }
    update();
}

void AScanPlot::onFPSEnabledChanged(bool value)
{
    _drawFPS = value;
}
