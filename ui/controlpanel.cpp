#include "controlpanel.h"
#include "ui_controlpanel.h"

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    _core(0),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);

    /*for(int i=0; i<30; i++) {
        TouchSpinBox * wid = new TouchSpinBox("Control #" + QString::number(i));
        ui->scrollLayout->addWidget(wid);
    }*/
    tvgCurve = new TouchSpinBox("TVG");
    ui->scrollLayout->addWidget(tvgCurve);
    for(int i=0; i<30; i++) {
            TouchSpinBox * wid = new TouchSpinBox("Control #" + QString::number(i));
            ui->scrollLayout->addWidget(wid);
    }
    QObject::connect(tvgCurve,SIGNAL(valueChanged(double)),this,SLOT(tvgChanged(double)));

}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::setCore(Core *ptr)
{
    _core = ptr;
}

void ControlPanel::refreshValues()
{

}

void ControlPanel::tvgChanged(double value)
{
    _core->setTvgCurve(value);
}
