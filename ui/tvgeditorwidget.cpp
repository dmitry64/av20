#include "tvgeditorwidget.h"
#include "ui_tvgeditorwidget.h"

#include "device/tvg/tvgsinglepoint.h"

TVGEditorWidget::TVGEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TVGEditorWidget)
{
    ui->setupUi(this);
    ui->singleOffset->setName("Offset");
    ui->singleOffset->setValue(0);
    ui->singleOffset->setSuffix("us");
    ui->singleHeight->setName("Height");
    ui->singleHeight->setValue(0);
    ui->singleType->setName("Type");
    std::vector<QString> types;
    types.push_back("Line");
    types.push_back("Curve");
    ui->singleType->setValues(types);
    _core = 0;
    _currentChannel = 0;
    connect(ui->singleHeight,SIGNAL(valueChanged(double)),this,SLOT(onSingleHeightChanged(double)));
    connect(ui->singleOffset,SIGNAL(valueChanged(double)),this,SLOT(onSingleOffsetChanged(double)));
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
    if(curve->getType() == TVGType::TVGSimple) {
        TVGSinglePoint * single = static_cast<TVGSinglePoint*> (curve);
        ui->singleHeight->setValue(qRound(single->getYHeight()*200.0));
        ui->singleOffset->setValue(qRound(single->getXOffset()*200.0));

    }
    update();
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
    init(channel);
}

void TVGEditorWidget::onSingleOffsetChanged(double value)
{
    TVGCurve * curve = 0;
    curve = new TVGSinglePoint(value/200.0,ui->singleHeight->value()/200.0);
    ui->aScanWidget->drawTempTVG(curve);
    delete curve;
}

void TVGEditorWidget::onSingleHeightChanged(double value)
{
    TVGCurve * curve = 0;
    curve = new TVGSinglePoint(ui->singleOffset->value()/200.0,value/200.0);
    ui->aScanWidget->drawTempTVG(curve);
    delete curve;
}


void TVGEditorWidget::on_applyButton_released()
{
    TVGCurve * curve = 0;
    curve = new TVGSinglePoint(ui->singleOffset->value()/200.0,ui->singleHeight->value()/200.0);
    _core->setTVG(_currentChannel,curve);
    //ui->aScanWidget->applyTempCurve();
    delete curve;
}
