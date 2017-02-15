#include "ascaninfowidget.h"
#include "ui_ascaninfowidget.h"

AScanInfoWidget::AScanInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AScanInfoWidget)
{
    ui->setupUi(this);
}

AScanInfoWidget::~AScanInfoWidget()
{
    delete ui;
}
