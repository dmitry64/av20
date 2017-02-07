#include "controlpanel.h"
#include "ui_controlpanel.h"
#include "ui/controls/touchspinbox.h"

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);


    for(int i=0; i<30; i++) {
        TouchSpinBox * wid = new TouchSpinBox();
        ui->scrollLayout->addWidget(wid);
    }


}

ControlPanel::~ControlPanel()
{
    delete ui;
}
