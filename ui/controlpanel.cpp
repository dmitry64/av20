#include "controlpanel.h"
#include "ui_controlpanel.h"

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

    _gateCounter = 0;
    _gatesLayout = new QVBoxLayout();
    ui->scrollLayout->addLayout(_gatesLayout);

    _addGateButton = new AddGateButton();
    ui->scrollLayout->addWidget(_addGateButton);
    connect(_addGateButton, SIGNAL(addGate()),this,SLOT(onAddGate()));

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


void ControlPanel::init(const ChannelsCalibration & calibration)
{
    const auto & channel = calibration.getChannel(_info._channel);
    _prismTimeSpinbox->setValue(channel.getDisplayChannels()[_info._displayChannel].getRx().getPrismTime());
    _gateCounter = 0;
    for(size_t i=0; i<_gates.size(); i++) {
        _gatesLayout->removeWidget(_gates[i]);
        delete _gates[i];
    }
    _gates.clear();

    const auto & dispChannel = calibration.getDisplayChannel(_info);
    const std::vector<Gate> & gates = dispChannel.gates();
    for(size_t i=0; i<gates.size(); i++) {
        GateController * gateController = new GateController();
        gateController->setGate(gates[i]);
        _gates.push_back(gateController);
        _gatesLayout->addWidget(gateController);
        connect(gateController,SIGNAL(deleteGate(Gate,GateController*)),this,SLOT(onDeleteGate(Gate,GateController*)));
        connect(gateController,SIGNAL(gateChanged(Gate)),this,SLOT(onGateChanged(Gate)));
        _gateCounter++;
    }
    update();
}

void ControlPanel::onGateChanged(Gate gate)
{
    Q_ASSERT(_core);
    _core->modifyGate(_info,gate);
    update();
}

void ControlPanel::onDeleteGate(Gate gate, GateController *controller)
{
    _gateCounter--;
    controller->hide();
    _gatesLayout->removeWidget(controller);
    auto it = _gates.begin();
    while(it!=_gates.end()) {
        if(it.operator *() == controller) {
            break;
        }
        it++;
    }
    _gates.erase(it);
    _core->removeGate(_info,gate._id);
    update();
}

void ControlPanel::onAddGate()
{
    Gate gate;
    gate._start = 50;
    gate._finish = 150;
    gate._level = 50;
    gate._id = _gateCounter;
    _gateCounter++;
    _core->addGate(_info,gate);
    GateController * gateController = new GateController();
    gateController->setGate(gate);
    _gates.push_back(gateController);
    _gatesLayout->addWidget(gateController);
    connect(gateController,SIGNAL(deleteGate(Gate,GateController*)),this,SLOT(onDeleteGate(Gate,GateController*)));
    connect(gateController,SIGNAL(gateChanged(Gate)),this,SLOT(onGateChanged(Gate)));
    update();
}

void ControlPanel::onPrismTimeChanged(double value)
{
    Q_ASSERT(_core);
    _core->setPrismTime(_info,value);
}
