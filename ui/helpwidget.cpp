#include "helpwidget.h"
#include "ui_helpwidget.h"
#include "system/system.h"

HelpWidget::HelpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWidget)
{
    ui->setupUi(this);
    updateFiles();
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

HelpWidget::~HelpWidget()
{
    delete ui;
}

void HelpWidget::updateFiles()
{
    System * system = System::getInstance();
    ui->listWidget->addItems(system->getFilesystem()->getHelpList());
}

void HelpWidget::on_listWidget_itemSelectionChanged()
{
    System * system = System::getInstance();
    QString filename = ui->listWidget->selectedItems().first()->data(0).toString();
    QFile help(system->getFilesystem()->getHelpPath() + "/" + filename);
    if(help.open(QIODevice::ReadOnly)) {
        QString html = help.readAll();
        ui->textBrowser->setHtml(html);
    }
    else {
        ui->textBrowser->setText("Error! Cannot open file!");
    }
}
