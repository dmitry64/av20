#include "debuggui.h"
#include "ui_debuggui.h"
#include <QDebug>

DebugGUI::DebugGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugGUI)
{
    ui->setupUi(this);
    _core = 0;
    connect(this,SIGNAL(ascan(AScan)),ui->ascanWidget,SLOT(onAScan(AScan)));
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

AScanWidget *DebugGUI::getAscanWidget()
{
    return ui->ascanWidget;
}

ControlPanel *DebugGUI::getControlPanel()
{
    return ui->controlPanel;
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
    emit ascan(scan);
}

void DebugGUI::on_exitButton_released()
{
    QApplication::exit(0);
}
