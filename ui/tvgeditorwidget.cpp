#include "tvgeditorwidget.h"
#include "ui_tvgeditorwidget.h"
#include <QDebug>
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
    _info._channel = 0;
    _info._displayChannel = 0;
    connect(ui->singleHeight,SIGNAL(valueChanged(double)),this,SLOT(onSingleHeightChanged(double)));
    connect(ui->singleOffset,SIGNAL(valueChanged(double)),this,SLOT(onSingleOffsetChanged(double)));
    connect(ui->singleWidth,SIGNAL(valueChanged(double)),this,SLOT(onSingleWidthChanged(double)));
    connect(ui->singleBase,SIGNAL(valueChanged(double)),this,SLOT(onSingleBaseChanged(double)));
    connect(ui->singleForm,SIGNAL(valueChanged(double)),this,SLOT(onSingleFormChanged(double)));

    connect(ui->channelSelector,SIGNAL(channelChanged(ChannelsInfo)),this,SLOT(setChannel(ChannelsInfo)));
}

TVGEditorWidget::~TVGEditorWidget()
{
    delete ui;
}

void TVGEditorWidget::reset()
{
    ui->aScanWidget->reset();
}

void TVGEditorWidget::init(ChannelsInfo info)
{
    const ChannelsCalibration & snapshot = _core->getCalibrationsSnapshot();
    init(info,snapshot);
}

void TVGEditorWidget::init(ChannelsInfo info, const ChannelsCalibration & snapshot)
{
    _info = info;
    ui->aScanWidget->setChannelInfo(snapshot.getChannel(_info._channel),_info._displayChannel);
    initCurve(snapshot.getChannel(_info._channel).getRx().getTvgCurve());
    ui->channelSelector->init(snapshot);
    update();
}

void TVGEditorWidget::initCurve(const TVGCurve *curve)
{
    Q_ASSERT(curve);
    if(curve->getType() == TVGType::TVGSimple) {
        const TVGSinglePoint * single = static_cast<const TVGSinglePoint*> (curve);
        ui->singleHeight->setValue(qRound(single->getYHeight()));
        ui->singleOffset->setValue(qRound(single->getXOffset()));
        ui->singleBase->setValue(qRound(single->getYBase()));
        ui->singleWidth->setValue(qRound(single->getXWidth()));
        ui->singleForm->setValue(qRound(single->getCurve()));
    }
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

void TVGEditorWidget::onChannelChanged(Channel channel)
{
    ui->aScanWidget->onChannelChanged(channel);
}

void TVGEditorWidget::setChannel(ChannelsInfo info)
{
    const ChannelsCalibration & snapshot = _core->getCalibrationsSnapshot();
    _info = info;
    ui->aScanWidget->setChannelInfo(snapshot.getChannel(_info._channel),_info._displayChannel);
    initCurve(snapshot.getChannel(_info._channel).getRx().getTvgCurve());
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
    _core->setTVG(_info._channel,curve);
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
    _core->setTVG(_info._channel,curve);
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
    _core->setTVG(_info._channel,curve);
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
    _core->setTVG(_info._channel,curve);
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
    _core->setTVG(_info._channel,curve);
    delete curve;
}
