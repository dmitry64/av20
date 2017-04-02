#include "helpwidget.h"
#include "ui_helpwidget.h"
#include "system/system.h"
#include <QIODevice>
#include <QFile>
#include <QList>
#include <QListWidgetItem>

HelpWidget::HelpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWidget)
{
    ui->setupUi(this);
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    updateFiles();

}

HelpWidget::~HelpWidget()
{
    delete ui;
}

void HelpWidget::updateFiles()
{
    System * system = System::getInstance();
    Q_ASSERT(system);
    ui->listWidget->addItems(system->getFilesystem()->getHelpList());
}

void HelpWidget::on_listWidget_itemSelectionChanged()
{
    System * system = System::getInstance();
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.size() > 0) {
        QListWidgetItem * item = items.first();
        Q_ASSERT(item);

        QString filename = item->data(0).toString();
        Q_ASSERT(!filename.isEmpty());
        QFile help(system->getFilesystem()->getHelpPath() + "/" + filename);
        Q_ASSERT(help.exists());
        if(help.open(QIODevice::ReadOnly)) {
            QString html = help.readAll();
            ui->textBrowser->setHtml(html);
        }
        else {
            ui->textBrowser->setText("Error! Cannot open file!");
            qDebug() << "Error reading help file";
        }
    }
}
