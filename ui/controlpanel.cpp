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

    _sensBaseLevel = new TouchSpinBox("Sens");
    ui->scrollLayout->addWidget(_sensBaseLevel);
    for(int i=0; i<30; i++) {
            TouchSpinBox * wid = new TouchSpinBox("Control #" + QString::number(i));
            ui->scrollLayout->addWidget(wid);
    }
    QObject::connect(_sensBaseLevel,SIGNAL(valueChanged(double)),this,SLOT(sensChanged(double)));

}

void ControlPanel::showEvent(QShowEvent *event) {
    QWidget::showEvent( event );
    init();
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

void ControlPanel::setChannel(int channel)
{
    _currentChannel = channel;
}

void ControlPanel::init()
{
    DeviceCalibration * calibration = _core->getSnapshot();

    _sensBaseLevel->setValue(calibration->getChannel(_currentChannel)->baseSensLevel());

    delete calibration;
}

void ControlPanel::sensChanged(double value)
{
    _core->setChannelBaseSens(_currentChannel, value);
}
