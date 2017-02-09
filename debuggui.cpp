#include "debuggui.h"
#include "ui_debuggui.h"
#include <QDebug>

DebugGUI::DebugGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugGUI)
{
    ui->setupUi(this);
    _core = 0;
    connect(this,SIGNAL(AScanSingle(AScan)),ui->ascanWidgetSingle,SLOT(onAScan(AScan)));
    connect(this,SIGNAL(AScanAB(AScan)),ui->ascanWidgetAB,SLOT(onAScan(AScan)));

    connect(this,SIGNAL(TVGReady(TVG)),ui->ascanWidgetSingle,SLOT(onTVG(TVG)));
    connect(this,SIGNAL(TVGReady(TVG)),ui->ascanWidgetAB,SLOT(onTVG(TVG)));
}

DebugGUI::~DebugGUI()
{
    delete ui;
}

void DebugGUI::setCore(Core *core)
{
    _core = core;
    ui->controlPanel->setCore(core);
}

AScanWidget *DebugGUI::getAscanWidgetSingle()
{
    return ui->ascanWidgetSingle;
}

ControlPanel *DebugGUI::getControlPanel()
{
    return ui->controlPanel;
}

void DebugGUI::init()
{
    if(_core!=0) {
        DeviceCalibration * calibration = _core->getSnapshot();

        // TODO: apply

        delete calibration;
    }
}

void DebugGUI::showEvent(QShowEvent *event) {
    QWidget::showEvent( event );
    init();
}

void DebugGUI::debug(int value)
{
    ui->progressBar->setValue(value % 100);
}

void DebugGUI::onConnectionStatusChanged(bool status)
{
    ui->connectionCheckBox->setChecked(status);
}

void DebugGUI::onErrorStatusChanged(bool status)
{
    ui->errorCheckBox->setChecked(status);
}

void DebugGUI::onDeviceErrorStatusChanged(bool status)
{
    ui->deviceErrorCheckBox->setChecked(status);
}

void DebugGUI::onDeviceOverheatStatusChanged(bool status)
{
    ui->overheatCheckBox->setChecked(status);
}

void DebugGUI::onDeviceReadyStatusChanged(bool status)
{
    ui->deviceReadyCheckBox->setChecked(status);
}

void DebugGUI::onAScan(AScan scan)
{
    if(ui->tabWidget->currentIndex() == 0) {
        emit AScanAB(scan);
    } else {
        emit AScanSingle(scan);
    }
}

void DebugGUI::onTVG(TVG tvg)
{
    emit TVGReady(tvg);
}

void DebugGUI::on_exitButton_released()
{
    QApplication::exit(0);
}

void DebugGUI::on_pushButton_2_released()
{
    if(ui->controlPanel->isHidden()) {
        ui->controlPanel->show();
    } else {
        ui->controlPanel->hide();
    }
}
