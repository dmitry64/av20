#include "memorywidget.h"
#include "ui_memorywidget.h"

#include "system/system.h"

MemoryWidget::MemoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryWidget)
{
    ui->setupUi(this);


    update();
}

MemoryWidget::~MemoryWidget()
{
    delete ui;
}

void MemoryWidget::update()
{
    Filesystem * fs = System::getInstance()->getFilesystem();
    ui->dataList->insertItems(0,fs->getDataList());
    ui->mediaList->insertItems(0,fs->getMediaList());
}
