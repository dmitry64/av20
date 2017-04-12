#include "tvgeditorwidget.h"
#include "ui_tvgeditorwidget.h"
#include <QDebug>


void TVGEditorWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    switchToSelectedChannel();
}

TVGTwoPoints *TVGEditorWidget::createTVGTwoPointsFromValues()
{
    double base = ui->singleBase->value();
    double height = ui->singleHeight->value();
    double width = ui->singleWidth->value();
    double offset = ui->singleOffset->value();
    double form = ui->singleForm->value();
    return new TVGTwoPoints(base, offset, width, height, form);
}

TVGNPoints *TVGEditorWidget::createTVGNPointsFromValues()
{
    TVGNPoints * tvg = new TVGNPoints();
    tvg->setPoints(_npointsValues);
    return tvg;
}

void TVGEditorWidget::initNPointButtons()
{
    for(auto it=_npointsControls.begin(); it!=_npointsControls.end(); it++) {
        VerticalTouchSpinBox * control = it.operator*();
        control->hide();
        ui->npointLayout->removeWidget(control);
        disconnect(control,SIGNAL(valueChanged(double)),this,SLOT(onNPointValueChanged(double)));
        delete control;
    }
    _npointsControls.clear();

    for(int i=0; i<_npointNumber; i++) {
        const std::pair<double,double> & point = _npointsValues.at(i);
        VerticalTouchSpinBox * control = new VerticalTouchSpinBox();
        control->setIndex(i);
        control->setMin(0);
        control->setMax(80);
        control->setName(QString::number(qRound(point.first * 200.0))+tr("us"));
        control->setStep(1);
        control->setValue((point.second)*80.0);
        control->setSuffix(tr("dB"));
        ui->npointLayout->addWidget(control);
        _npointsControls.push_back(control);
        connect(control,SIGNAL(valueChanged(double)),this,SLOT(onNPointValueChanged(double)));
        control->show();
    }
}

void TVGEditorWidget::updateNPointsTVG()
{
    TVGNPoints * curve = new TVGNPoints();
    curve->setPoints(_npointsValues);
    _core->setTVG(_info,curve);
    delete curve;
}

void TVGEditorWidget::setupTwoPoint()
{
    ui->singleOffset->setName(tr("Offset - To (us)"));
    ui->singleOffset->setValue(100);
    ui->singleOffset->setMax(200.0);
    ui->singleOffset->setSuffix("us");
    ui->singleHeight->setName(tr("Height - A (dB)"));
    ui->singleHeight->setValue(30);
    ui->singleHeight->setMax(80.0);
    ui->singleHeight->setSuffix("dB");
    ui->singleForm->setName(tr("Form - Ki (0 - 50)"));
    ui->singleForm->setValue(15);
    ui->singleForm->setMax(50);
    ui->singleWidth->setName(tr("Width - T (us)"));
    ui->singleWidth->setValue(60);
    ui->singleWidth->setMax(200.0);
    ui->singleWidth->setSuffix("us");
    ui->singleBase->setName(tr("Base - B (dB)"));
    ui->singleBase->setValue(70);
    ui->singleBase->setMax(80.0);
    ui->singleBase->setSuffix("dB");

    connect(ui->singleHeight,SIGNAL(valueChanged(double)),this,SLOT(onSingleHeightChanged(double)));
    connect(ui->singleOffset,SIGNAL(valueChanged(double)),this,SLOT(onSingleOffsetChanged(double)));
    connect(ui->singleWidth,SIGNAL(valueChanged(double)),this,SLOT(onSingleWidthChanged(double)));
    connect(ui->singleBase,SIGNAL(valueChanged(double)),this,SLOT(onSingleBaseChanged(double)));
    connect(ui->singleForm,SIGNAL(valueChanged(double)),this,SLOT(onSingleFormChanged(double)));
}

TVGEditorWidget::TVGEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TVGEditorWidget)
{
    ui->setupUi(this);
    _core = 0;
    _info._channel = 0;
    _info._displayChannel = 0;

    setupTwoPoint();

    ui->npointNumber->setName("N");
    ui->npointNumber->setMin(2);
    ui->npointNumber->setMax(16);
    ui->npointNumber->setValue(0);
    ui->npointNumber->setStep(1);

    _npointsValues.push_back(std::pair<double,double>(0.0,0.6));
    _npointsValues.push_back(std::pair<double,double>(1.0,0.6));

    connect(ui->npointNumber,SIGNAL(valueChanged(double)),this,SLOT(onNPointNumberChanged(double)));
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

void TVGEditorWidget::init(const ChannelsInfo &info)
{
    const ChannelsCalibration & snapshot = _core->getCalibrationsSnapshot();
    init(info,snapshot);
}

void TVGEditorWidget::init(const ChannelsInfo & info, const ChannelsCalibration & snapshot)
{
    logEvent("TVGEditor","Initializing");

    const ChannelID channel = _info._channel;
    const DisplayChannelID displayChannel = _info._displayChannel;
    _info = info;

    ui->aScanWidget->setChannelInfo(snapshot.getChannel(channel),_info._displayChannel);
    const std::vector<DisplayChannel> & dispChans = snapshot.getChannel(channel).getDisplayChannels();
    Q_ASSERT(dispChans.size());
    const DisplayChannel & dc = dispChans.at(displayChannel);
    const RxChannel & rx = dc.getRx();
    const TVGCurve * curve = rx.getTvgCurve();
    Q_ASSERT(curve);
    initCurve(curve);
    ui->channelSelector->init(snapshot);
    update();
}

void TVGEditorWidget::initCurve(const TVGCurve *curve)
{
    Q_ASSERT(curve);
    switch(curve->getType()) {
    case TVGType::TVG2PointType: {
        const TVGTwoPoints * single = static_cast<const TVGTwoPoints*> (curve);
        ui->singleHeight->setValue(qRound(single->getYHeight()));
        ui->singleOffset->setValue(qRound(single->getXOffset()));
        ui->singleBase->setValue(qRound(single->getYBase()));
        ui->singleWidth->setValue(qRound(single->getXWidth()));
        ui->singleForm->setValue(qRound(single->getCurve()));
        ui->tabWidget->setCurrentIndex(0);
    }
    break;
    case TVGType::TVGNPointType: {
        const std::vector<std::pair<double,double> > & pairs = curve->getReferencePoints();
        ui->npointNumber->setValue(pairs.size());
        _npointNumber = pairs.size();
        _npointsValues = pairs;
        initNPointButtons();
        ui->tabWidget->setCurrentIndex(1);
    }
    break;
    }

}

void TVGEditorWidget::setCore(Core *core)
{
    _core = core;
    ui->channelSelector->setCore(core);
}

void TVGEditorWidget::switchToSelectedChannel()
{
    const auto & info = ui->channelSelector->selectedChannel();
    setChannel(info);
}

void TVGEditorWidget::onDisplayPackage(QSharedPointer<DisplayPackage> package)
{
    ui->aScanWidget->onAScan(package->_ascan);
}

void TVGEditorWidget::onChannelChanged(Channel channel)
{
    ui->aScanWidget->onChannelChanged(channel);
}

void TVGEditorWidget::setChannel(ChannelsInfo info)
{
    const ChannelsCalibration & snapshot = _core->getCalibrationsSnapshot();
    _info = info;
    _core->switchChannel(info);
    ui->aScanWidget->setChannelInfo(snapshot.getChannel(_info._channel),_info._displayChannel);
    initCurve(snapshot.getChannel(_info._channel).getDisplayChannels()[info._displayChannel].getRx().getTvgCurve());
}

void TVGEditorWidget::onSingleOffsetChanged(double value)
{
    Q_UNUSED(value);
    TVGCurve * curve = createTVGTwoPointsFromValues();

    _core->setTVG(_info,curve);
    delete curve;
}

void TVGEditorWidget::onSingleHeightChanged(double value)
{
    Q_UNUSED(value);
    TVGCurve * curve = createTVGTwoPointsFromValues();
    _core->setTVG(_info,curve);
    delete curve;
}

void TVGEditorWidget::onSingleBaseChanged(double value)
{
    Q_UNUSED(value);
    TVGCurve * curve = createTVGTwoPointsFromValues();
    _core->setTVG(_info,curve);
    delete curve;
}

void TVGEditorWidget::onSingleWidthChanged(double value)
{
    Q_UNUSED(value);
    TVGCurve * curve =  createTVGTwoPointsFromValues();
    _core->setTVG(_info,curve);
    delete curve;
}

void TVGEditorWidget::onSingleFormChanged(double value)
{
    Q_UNUSED(value);
    TVGCurve * curve = createTVGTwoPointsFromValues();
    _core->setTVG(_info,curve);
    delete curve;
}

void TVGEditorWidget::onNPointNumberChanged(double value)
{
    Q_ASSERT(value<=16);
    Q_ASSERT(value>1);
    double step = 1.0/(value-1);
    Q_ASSERT(step!=0.0);
    std::vector<std::pair<double, double> > values;
    int i = 0;
    for(auto it=_npointsValues.begin(); it!=_npointsValues.end(); it++) {
        if(i<value) {
            values.push_back(std::pair<double,double>(std::min(1.0,i*step),it.operator*().second));
            i++;
        }
    }

    while(i<value) {
        values.push_back(std::pair<double,double>(std::min(1.0,i*step),0.6));
        i++;
    }
    Q_ASSERT(i<=16);
    _npointsValues = values;
    _npointNumber = value;

    updateNPointsTVG();
    initNPointButtons();
}

void TVGEditorWidget::onNPointValueChanged(double value)
{
    VerticalTouchSpinBox * control = qobject_cast<VerticalTouchSpinBox*>(sender());
    Q_ASSERT(control);
    _npointsValues[control->index()].second = std::max(std::min(value/80.0,1.0),0.0);
    updateNPointsTVG();
}


void TVGEditorWidget::on_tabWidget_currentChanged(int index)
{
    switch(index) {
    case 0: {
        TVGCurve * curve = createTVGTwoPointsFromValues();
        Q_ASSERT(curve);
        _core->setTVG(_info,curve);
        initCurve(curve);
        delete curve;
    }
    break;
    case 1: {
        TVGCurve * curve = createTVGNPointsFromValues();
        Q_ASSERT(curve);
        _core->setTVG(_info,curve);
        initCurve(curve);
        delete curve;
    }
    break;
    }
}
