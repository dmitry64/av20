#include "memorywidget.h"
#include "ui_memorywidget.h"

#include "system/system.h"

void MemoryWidget::showEvent(QShowEvent *event)
{
    update();
}

MemoryWidget::MemoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryWidget)
{
    ui->setupUi(this);
}

MemoryWidget::~MemoryWidget()
{
    delete ui;
}

void MemoryWidget::init()
{
    update();
}

void MemoryWidget::update()
{
    ui->dataList->clear();
    ui->mediaList->clear();
    Filesystem * fs = System::getInstance()->getFilesystem();
    ui->dataList->insertItems(0,fs->getDataList());
    ui->mediaList->insertItems(0,fs->getMediaList());
}

void MemoryWidget::on_removeButton_released()
{
    Filesystem * fs = System::getInstance()->getFilesystem();
    switch(ui->tabWidget->currentIndex()) {
    case 0: {
        auto dataItems = ui->dataList->selectedItems();
        for(auto it=dataItems.begin(); it!=dataItems.end(); it++) {
            const auto & item = it.operator *();
            QString name = item->data(0).toString();
            QFile file(fs->getDataPath()+"/"+name);
            file.remove();
        }
    }
    break;
    case 1: {
        auto mediaItems = ui->mediaList->selectedItems();
        for(auto it=mediaItems.begin(); it!=mediaItems.end(); it++) {
            const auto & item = it.operator *();
            QString name = item->data(0).toString();
            QFile file(fs->getMediaPath()+"/"+name);
            file.remove();
        }
    }
    break;
    default:
        break;

    }
    update();
}

void MemoryWidget::on_refreshButton_released()
{
    update();
}
