#include "modeselectionwidget.h"
#include "ui_modeselectionwidget.h"

ModeSelectionWidget::ModeSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeSelectionWidget)
{
    ui->setupUi(this);
}

ModeSelectionWidget::~ModeSelectionWidget()
{
    delete ui;
}
