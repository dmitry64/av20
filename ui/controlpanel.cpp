#include "controlpanel.h"
#include "ui_controlpanel.h"
#include "controls/widescrollbar.h"

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    _core(0),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);

    _prismTimeSpinbox = new TouchSpinBox();
    _prismTimeSpinbox->setName("Prism time");
    _prismTimeSpinbox->setMin(0);
    _prismTimeSpinbox->setMax(50);
    _prismTimeSpinbox->setValue(0);
    _prismTimeSpinbox->setSuffix("us");
    ui->scrollLayout->addWidget(_prismTimeSpinbox);
    connect(_prismTimeSpinbox,SIGNAL(valueChanged(double)),this,SLOT(onPrismTimeChanged(double)));

    _markerPositionSpinbox = new TouchSpinBox();
    _markerPositionSpinbox->setName("Marker");
    _markerPositionSpinbox->setMin(0);
    _markerPositionSpinbox->setMax(800);
    _markerPositionSpinbox->setValue(0);
    _markerPositionSpinbox->setSuffix("us");
    _markerPositionSpinbox->hide();
    ui->scrollLayout->addWidget(_markerPositionSpinbox);

    _frequencySpinbox = new TouchSpinBoxString();
    _frequencySpinbox->setValues(FreqStrings);
    _frequencySpinbox->setName("Frequency");
    ui->scrollLayout->addWidget(_frequencySpinbox);

    _progSpinbox = new TouchSpinBoxString();
    _progSpinbox->setValues(ProgStrings);
    _progSpinbox->setName("Program");
    ui->scrollLayout->addWidget(_progSpinbox);

    _gatesLayout = new QVBoxLayout();
    ui->scrollLayout->addLayout(_gatesLayout);

    _addGateButton = new AddGateButton();
    ui->scrollLayout->addWidget(_addGateButton);
    connect(_addGateButton, SIGNAL(addGate()),this,SLOT(onAddGate()));

    WideScrollBar * sb = new WideScrollBar();
    ui->scrollArea->setVerticalScrollBar(sb);

    _prevGatesCount = 0;

    //_gateCounter = 0;
    _info._channel = 0;
    _info._displayChannel = 0;
}

void ControlPanel::showEvent(QShowEvent *event)
{
    QWidget::showEvent( event );
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


void ControlPanel::init(const Channel & channel)
{
    //const auto & channel = calibration.getChannel(_info._channel);
    _prismTimeSpinbox->setValue(channel.getDisplayChannels()[_info._displayChannel].getRx().getPrismTime());

    const auto & dispChannels = channel.getDisplayChannels();
    const DisplayChannel & dc = dispChannels.at(_info._displayChannel);

    const std::vector<Gate> & gates = dc.gates();
    if(_prevGatesCount!=gates.size()) {
        _prevGatesCount = gates.size();

        for(size_t i=0; i<_gates.size(); i++) {
            _gatesLayout->removeWidget(_gates[i]);
            disconnect(_gates[i],SIGNAL(deleteGate(Gate,GateController*)),this,SLOT(onDeleteGate(Gate,GateController*)));
            disconnect(_gates[i],SIGNAL(gateChanged(Gate)),this,SLOT(onGateChanged(Gate)));
            delete _gates[i];
        }
        _gates.clear();


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
}

void ControlPanel::onGateChanged(Gate gate)
{
    Q_ASSERT(_core);
    _core->modifyGate(_info,gate);
    update();
}

void ControlPanel::onDeleteGate(Gate gate, GateController *controller)
{
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
