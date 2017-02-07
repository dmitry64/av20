#include "debuggui.h"
#include "ui_debuggui.h"
#include <QDebug>

DebugGUI::DebugGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugGUI)
{
    ui->setupUi(this);
    _core = 0;
}

DebugGUI::~DebugGUI()
{
    delete ui;
}

void DebugGUI::setCore(Core *core)
{
    _core = core;
    qDebug() << "set core!";
    ui->widget->setSource(core->getAscanPtr());
    qDebug() << "set core2!";
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
