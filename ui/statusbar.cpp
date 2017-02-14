#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);
    ui->overheatButton->hide();
    ui->errorButton->hide();
    ui->connectionErrorButton->hide();
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::onDeviceOverheatEnabled()
{
    ui->overheatButton->show();
}

void StatusBar::onDeviceOverheatDisabled()
{
    ui->overheatButton->hide();
}

void StatusBar::onDeviceErrorEnabled()
{
    ui->errorButton->show();
}

void StatusBar::onDeviceErrorDisabled()
{
    ui->errorButton->hide();
}

void StatusBar::onDeviceConnectionErrorEnabled()
{
    ui->connectionErrorButton->show();
}

void StatusBar::onDeviceConnectionErrorDisabled()
{
    ui->connectionErrorButton->hide();
}
