#include "tvgeditorwidget.h"
#include "ui_tvgeditorwidget.h"

#include "device/tvg/tvgsinglepoint.h"

TVGEditorWidget::TVGEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TVGEditorWidget)
{
    ui->setupUi(this);
    ui->singleOffset->setName("Offset - To (us)");
    ui->singleOffset->setValue(0);
    ui->singleOffset->setMax(200.0);
    ui->singleOffset->setSuffix("us");
    ui->singleHeight->setName("Height - A (dB)");
    ui->singleHeight->setValue(0);
    ui->singleHeight->setMax(80.0);
    ui->singleHeight->setSuffix("dB");
    ui->singleForm->setName("Form - Ki (0 - 50)");
    ui->singleForm->setValue(0);
    ui->singleForm->setMax(50);
    ui->singleWidth->setName("Width - T (us)");
    ui->singleWidth->setValue(0);
    ui->singleWidth->setMax(200.0);
    ui->singleWidth->setSuffix("us");
    ui->singleBase->setName("Base - B (dB)");
    ui->singleBase->setValue(0);
    ui->singleBase->setMax(80.0);
    ui->singleBase->setSuffix("dB");

    _core = 0;
    _currentChannel = 0;
    connect(ui->singleHeight,SIGNAL(valueChanged(double)),this,SLOT(onSingleHeightChanged(double)));
    connect(ui->singleOffset,SIGNAL(valueChanged(double)),this,SLOT(onSingleOffsetChanged(double)));
    connect(ui->singleWidth,SIGNAL(valueChanged(double)),this,SLOT(onSingleWidthChanged(double)));
    connect(ui->singleBase,SIGNAL(valueChanged(double)),this,SLOT(onSingleBaseChanged(double)));
    connect(ui->singleForm,SIGNAL(valueChanged(double)),this,SLOT(onSingleFormChanged(double)));


    connect(ui->channelSelector,SIGNAL(channelChanged(uint8_t)),this,SLOT(setChannel(uint8_t)));
}

TVGEditorWidget::~TVGEditorWidget()
{
    delete ui;
}

void TVGEditorWidget::reset()
{
    ui->aScanWidget->reset();
}

void TVGEditorWidget::init(uint8_t channel)
{
    ChannelsCalibration * snapshot =  _core->getCalibrationsSnapshot();
    init(channel,snapshot);
    delete snapshot;
}

void TVGEditorWidget::init(uint8_t channel, ChannelsCalibration *snapshot)
{
    _currentChannel = channel;
    std::vector<Channel*> channels;
    channels.push_back((snapshot->getChannel(channel)));
    ui->aScanWidget->setChannelsInfo(channels);
    channels.clear();
    ui->channelSelector->init(snapshot);
    TVGCurve * curve = snapshot->getChannel(channel)->rx()->getTvgCurve();
    initCurve(curve);
    update();
}

void TVGEditorWidget::initCurve(TVGCurve *curve)
{
    Q_ASSERT(curve);
    if(curve->getType() == TVGType::TVGSimple) {
        TVGSinglePoint * single = static_cast<TVGSinglePoint*> (curve);
        ui->singleHeight->setValue(qRound(single->getYHeight()));
        ui->singleOffset->setValue(qRound(single->getXOffset()));
        ui->singleBase->setValue(qRound(single->getYBase()));
        ui->singleWidth->setValue(qRound(single->getXWidth()));
        ui->singleForm->setValue(qRound(single->getCurve()));
    }
    ui->aScanWidget->drawTempTVG(curve);
}

void TVGEditorWidget::setCore(Core *core)
{
    _core = core;
    ui->channelSelector->setCore(core);
}

void TVGEditorWidget::onDisplayPackage(QSharedPointer<DisplayPackage> package)
{
    ui->aScanWidget->onAScan(&(package->ascan));
}

void TVGEditorWidget::onChannelChanged(Channel * channel)
{
    ui->aScanWidget->onChannelChanged(channel);
}

void TVGEditorWidget::setChannel(uint8_t channel)
{
    _currentChannel = channel;
    ChannelsCalibration * snapshot = _core->getCalibrationsSnapshot();
    Q_ASSERT(snapshot);
    std::vector<Channel*> channels;
    Channel * chan = snapshot->getChannel(channel);
    Q_ASSERT(chan);
    channels.push_back(chan);
    ui->aScanWidget->setChannelsInfo(channels);
    initCurve(snapshot->getChannel(channel)->rx()->getTvgCurve());
    update();
    delete snapshot;
}

void TVGEditorWidget::onSingleOffsetChanged(double value)
{
    TVGCurve * curve = 0;
    double base = ui->singleBase->value();
    double height = ui->singleHeight->value();
    double width = ui->singleWidth->value();
    double offset = value;
    double form = ui->singleForm->value();
    curve = new TVGSinglePoint(base, offset, width, height, form);
    ui->aScanWidget->drawTempTVG(curve);
    _core->setTVG(_currentChannel,curve);
    delete curve;
}

void TVGEditorWidget::onSingleHeightChanged(double value)
{
    TVGCurve * curve = 0;
    double base = ui->singleBase->value();
    double height = value;
    double width = ui->singleWidth->value();
    double offset = ui->singleOffset->value();
    double form = ui->singleForm->value();
    curve = new TVGSinglePoint(base, offset, width, height, form);
    ui->aScanWidget->drawTempTVG(curve);
    _core->setTVG(_currentChannel,curve);
    delete curve;
}

void TVGEditorWidget::onSingleBaseChanged(double value)
{
    TVGCurve * curve = 0;
    double base = value;
    double height = ui->singleHeight->value();
    double width = ui->singleWidth->value();
    double offset = ui->singleOffset->value();
    double form = ui->singleForm->value();
    curve = new TVGSinglePoint(base, offset, width, height, form);
    ui->aScanWidget->drawTempTVG(curve);
    _core->setTVG(_currentChannel,curve);
    delete curve;
}

void TVGEditorWidget::onSingleWidthChanged(double value)
{
    TVGCurve * curve = 0;
    double base = ui->singleBase->value();
    double height = ui->singleHeight->value();
    double width = value;
    double offset = ui->singleOffset->value();
    double form = ui->singleForm->value();
    curve = new TVGSinglePoint(base, offset, width, height, form);
    ui->aScanWidget->drawTempTVG(curve);
    _core->setTVG(_currentChannel,curve);
    delete curve;
}

void TVGEditorWidget::onSingleFormChanged(double value)
{
    TVGCurve * curve = 0;
    double base = ui->singleBase->value();
    double height = ui->singleHeight->value();
    double width = ui->singleWidth->value();
    double offset = ui->singleOffset->value();
    double form = value;
    curve = new TVGSinglePoint(base, offset, width, height, form);
    ui->aScanWidget->drawTempTVG(curve);
    _core->setTVG(_currentChannel,curve);
    delete curve;
}

