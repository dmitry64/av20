#include "controlpanel.h"
#include "ui_controlpanel.h"
#include "controls/widescrollbar.h"

void ControlPanel::initPrismTime()
{
    _prismTimeSpinbox = new TouchSpinBox();
    _prismTimeSpinbox->setName(tr("Prism time"));
    _prismTimeSpinbox->setMin(0);
    _prismTimeSpinbox->setMax(50);
    _prismTimeSpinbox->setValue(0);
    _prismTimeSpinbox->setSuffix(tr("us"));
    ui->scrollLayout->addWidget(_prismTimeSpinbox);
    connect(_prismTimeSpinbox,SIGNAL(valueChanged(double)),this,SLOT(onPrismTimeChanged(double)));
}

void ControlPanel::initMerkerPos()
{
    _markerPositionSpinbox = new TouchSpinBox();
    _markerPositionSpinbox->setName(tr("Marker"));
    _markerPositionSpinbox->setMin(0);
    _markerPositionSpinbox->setMax(800);
    _markerPositionSpinbox->setValue(0);
    _markerPositionSpinbox->setSuffix(tr("us"));
    _markerPositionSpinbox->hide();
    ui->scrollLayout->addWidget(_markerPositionSpinbox);
}

void ControlPanel::initFreqency()
{
    _frequencySpinbox = new TouchSpinBoxString();
    _frequencySpinbox->setValues(FreqStrings);
    _frequencySpinbox->setName(tr("Frequency"));
    ui->scrollLayout->addWidget(_frequencySpinbox);
    connect(_frequencySpinbox,SIGNAL(indexChanged(size_t)),this,SLOT(onFrequencyChanged(size_t)));
}

void ControlPanel::initPulseProg()
{
    _progSpinbox = new TouchSpinBoxString();
    _progSpinbox->setValues(ProgStrings);
    _progSpinbox->setName(tr("Program"));
    ui->scrollLayout->addWidget(_progSpinbox);
    connect(_progSpinbox,SIGNAL(indexChanged(size_t)),this,SLOT(onPulseProgChanged(size_t)));
}

void ControlPanel::initGates()
{
    _gatesLayout = new QVBoxLayout();
    ui->scrollLayout->addLayout(_gatesLayout);

    _addGateButton = new AddGateButton();
    ui->scrollLayout->addWidget(_addGateButton);
    connect(_addGateButton, SIGNAL(addGate()),this,SLOT(onAddGate()));

    _prevGatesCount = 0;
}

void ControlPanel::initScrollbar()
{
    WideScrollBar * sb = new WideScrollBar();
    ui->scrollArea->setVerticalScrollBar(sb);
}

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    _core(0),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);

    initPrismTime();
    initMerkerPos();
    initFreqency();
    initPulseProg();
    initGates();
    initScrollbar();

    _oldChannel = 0;
    _info._channel = 0;
    _info._displayChannel = 0;
}

void ControlPanel::showEvent(QShowEvent *event)
{
    QWidget::showEvent( event );
}

void ControlPanel::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        _prismTimeSpinbox->setName(tr("Prism time"));
        _prismTimeSpinbox->setSuffix(tr("us"));
        _markerPositionSpinbox->setName(tr("Marker"));
        _frequencySpinbox->setName(tr("Frequency"));
        _progSpinbox->setName(tr("Program"));
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::setCore(Core *ptr)
{
    Q_ASSERT(ptr);
    _core = ptr;
}

void ControlPanel::setChannel(ChannelsInfo info)
{
    _info = info;
}

void ControlPanel::clearGates()
{
    for(auto it=_gates.begin(); it!=_gates.end(); it++) {
        GateController * gateController = it.operator*();
        Q_ASSERT(gateController);
        _gatesLayout->removeWidget(gateController);
        disconnect(gateController,SIGNAL(deleteGate(Gate,GateController*)),this,SLOT(onDeleteGate(Gate,GateController*)));
        disconnect(gateController,SIGNAL(gateChanged(Gate)),this,SLOT(onGateChanged(Gate)));
        delete gateController;
    }
    _gates.clear();
}

void ControlPanel::fillGates(const std::vector<Gate>& gates)
{
    _prevGatesCount = gates.size();

    clearGates();

    for(auto it=gates.begin(); it!=gates.end(); it++) {
        GateController * gateController = new GateController();
        gateController->setGate(it.operator*());
        _gates.push_back(gateController);
        _gatesLayout->addWidget(gateController);
        connect(gateController,SIGNAL(deleteGate(Gate,GateController*)),this,SLOT(onDeleteGate(Gate,GateController*)));
        connect(gateController,SIGNAL(gateChanged(Gate)),this,SLOT(onGateChanged(Gate)));
    }
    update();
}

void ControlPanel::init(const Channel & channel)
{
    const auto & dispChannels = channel.getDisplayChannels();

    _prismTimeSpinbox->setValue(dispChannels.at(_info._displayChannel).getRx().getPrismTime());
    const PulserFreq & freq = dispChannels.at(_info._displayChannel).getTx().freq();
    _frequencySpinbox->setIndex(static_cast<size_t>(freq));
    const PulserProg & prog = dispChannels.at(_info._displayChannel).getTx().prog();
    _progSpinbox->setIndex(static_cast<size_t>(prog));

    const DisplayChannel & dc = dispChannels.at(_info._displayChannel);

    const std::vector<Gate> & gates = dc.gates();
    if(_prevGatesCount!=gates.size() || _oldChannel!=channel.index() || _info._displayChannel != channel.getActiveDisplayChannelIndex()) {
        _oldChannel = channel.index();
        fillGates(gates);
    }
}

void ControlPanel::onGateChanged(Gate gate)
{
    Q_ASSERT(_core);
    _core->modifyGate(_info,gate);
    update();
}

void ControlPanel::onDeleteGate(Gate gate, GateController *controller)
{
    Q_UNUSED(controller);
    _core->removeGate(_info,gate._id);
}

void ControlPanel::onAddGate()
{
    Gate gate;
    gate._start = 50;
    gate._finish = 150;
    gate._level = 50;
    gate._id = 0;
    _core->addGate(_info,gate);
}

void ControlPanel::onPrismTimeChanged(double value)
{
    Q_ASSERT(_core);
    _core->setPrismTime(_info,value);
}

void ControlPanel::onFrequencyChanged(size_t index)
{
    PulserFreq freq = static_cast<PulserFreq>(index);
    _core->setPulserFreq(_info,freq);
}

void ControlPanel::onPulseProgChanged(size_t index)
{
    PulserProg prog = static_cast<PulserProg>(index);
    _core->setPulserProg(_info,prog);
}
