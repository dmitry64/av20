#include "menupanel.h"
#include "ui_menupanel.h"

MenuPanel::MenuPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuPanel)
{
    ui->setupUi(this);
}

MenuPanel::~MenuPanel()
{
    delete ui;
}
