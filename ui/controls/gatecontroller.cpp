#include "gatecontroller.h"
#include "ui_gatecontroller.h"
#include <QDebug>

void GateController::updateGate()
{
    ui->gateStart->setValue(_gate._start);
    ui->gateFinish->setValue(_gate._finish);
    ui->gateLevel->setValue(_gate._level);
    ui->gateButton->setText("Gate: "+QString::number(_gate._start)+"-"+QString::number(_gate._finish)+"\n"+
                            "Level: "+QString::number(_gate._level));
    ui->gateIcon->setColor(getColorByLevel(_gate._level));
    update();
}

GateController::GateController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GateController)
{
    ui->setupUi(this);
    ui->gateStart->setName("Gate start");
    ui->gateStart->setSuffix("us");
    ui->gateFinish->setName("Gate end");
    ui->gateFinish->setSuffix("us");
    ui->gateLevel->setName("Gate level");
    ui->gateLevel->setSuffix("mV");
    ui->gateLevel->setMax(255);
    ui->gateIcon->setIcon(QIcon(":/icons/resources/icons/arrows_fit_horizontal.png"));
    ui->gateIcon->setColor(Qt::red);
    ui->gateStart->hide();
    ui->gateFinish->hide();
    ui->gateLevel->hide();

    connect(ui->gateStart,SIGNAL(valueChanged(double)),this,SLOT(onStartChanged(double)));
    connect(ui->gateFinish,SIGNAL(valueChanged(double)),this,SLOT(onFinishChanged(double)));
    connect(ui->gateLevel,SIGNAL(valueChanged(double)),this,SLOT(onLevelChanged(double)));
}

GateController::~GateController()
{
    delete ui;
}

void GateController::setGate(const Gate &gate)
{
    _gate = gate;
    updateGate();
}

void GateController::on_gateButton_released()
{
    if(ui->gateStart->isVisible()) {
        ui->gateStart->hide();
        ui->gateFinish->hide();
        ui->gateLevel->hide();
    }
    else {
        ui->gateStart->show();
        ui->gateFinish->show();
        ui->gateLevel->show();
    }
}

void GateController::on_deleteButton_released()
{
    _dialog = new DeleteDialog();
    _dialog->open();
    connect(_dialog,SIGNAL(doDelete()),this,SLOT(onDeleteGate()));
    connect(_dialog,SIGNAL(doCancel()),_dialog,SLOT(deleteLater()));
}

void GateController::onStartChanged(double value)
{
    _gate._start = value;
    emit gateChanged(_gate);
    updateGate();
}

void GateController::onFinishChanged(double value)
{
    _gate._finish = value;
    emit gateChanged(_gate);
    updateGate();
}

void GateController::onLevelChanged(double value)
{
    _gate._level = value;
    emit gateChanged(_gate);
    updateGate();
}

void GateController::onDeleteGate()
{
    _dialog->deleteLater();
    emit deleteGate(_gate,this);
}
