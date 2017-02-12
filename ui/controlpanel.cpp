#include "controlpanel.h"
#include "ui_controlpanel.h"

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    _core(0),
    _currentChannel(0),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);

    _sensBaseLevel = new TouchSpinBox();
    _sensBaseLevel->setName("Base sens.");
    ui->scrollLayout->addWidget(_sensBaseLevel);

    _prismTimeSpinbox = new TouchSpinBox();
    _prismTimeSpinbox->setName("Prism time");
    ui->scrollLayout->addWidget(_prismTimeSpinbox);

    _gateCounter = 0;

    _gatesLayout = new QVBoxLayout();
    ui->scrollLayout->addLayout(_gatesLayout);

    _addGateButton = new AddGateButton();
    ui->scrollLayout->addWidget(_addGateButton);
    connect(_addGateButton, SIGNAL(addGate()),this,SLOT(onAddGate()));

    /*

    TouchSpinBox * gateStart = new TouchSpinBox("Gate start");
    TouchSpinBox * gateEnd = new TouchSpinBox("Gate end");
    TouchSpinBox * gateLevel = new TouchSpinBox("Gate level");
    TouchSpinBox * gateColor = new TouchSpinBox("Gate color");

    gatesLayout->addWidget(gateStart);
    gatesLayout->addWidget(gateEnd);
    gatesLayout->addWidget(gateLevel);
    gatesLayout->addWidget(gateColor);

    ui->scrollLayout->addLayout(gatesLayout);*/


    /*for(int i=0; i<30; i++) {
            TouchSpinBox * wid = new TouchSpinBox("Control #" + QString::number(i));
            ui->scrollLayout->addWidget(wid);
    }*/
    QObject::connect(_sensBaseLevel,SIGNAL(valueChanged(double)),this,SLOT(sensChanged(double)));

}

void ControlPanel::showEvent(QShowEvent *event) {
    QWidget::showEvent( event );
    //init();
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::setCore(Core *ptr)
{
    _core = ptr;
}

void ControlPanel::setMode(uint8_t deviceMode)
{

}

void ControlPanel::setChannel(uint8_t channel)
{
    _currentChannel = channel;
    _gateCounter = 0;
    for(int i=0; i<_gates.size(); i++) {
        _gatesLayout->removeWidget(_gates[i]);
        delete _gates[i];
    }
    _gates.clear();
}

void ControlPanel::init(DeviceCalibration * calibration)
{
    _sensBaseLevel->setValue(calibration->getChannel(_currentChannel)->baseSensLevel());

    std::vector<Gate> gates = calibration->getChannel(_currentChannel)->gates();
    for(uint8_t i=0; i<gates.size(); i++) {
        GateController * gateController = new GateController();
        gateController->setGate(gates[i]);
        _gates.push_back(gateController);
        _gatesLayout->addWidget(gateController);
        connect(gateController,SIGNAL(deleteGate(Gate,GateController*)),this,SLOT(onDeleteGate(Gate,GateController*)));
        _gateCounter++;
    }
}

void ControlPanel::sensChanged(double value)
{
    _core->setChannelBaseSens(_currentChannel, value);
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
    _core->removeGate(_currentChannel,gate._id);
}

void ControlPanel::onAddGate()
{
    Gate gate;
    gate._start = 50;
    gate._finish = 150;
    gate._level = 50;
    gate._id = _gateCounter;
    _gateCounter++;
    _core->addGate(_currentChannel,gate);
    GateController * gateController = new GateController();
    gateController->setGate(gate);
    _gates.push_back(gateController);
    _gatesLayout->addWidget(gateController);
    connect(gateController,SIGNAL(deleteGate(Gate,GateController*)),this,SLOT(onDeleteGate(Gate,GateController*)));
}
