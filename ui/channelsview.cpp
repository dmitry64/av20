#include "channelsview.h"
#include "ui_channelsview.h"
#include <QTableWidgetItem>
#include <QDebug>
#include "controls/channelstableitem.h"

ChannelsView::ChannelsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelsView)
{
    ui->setupUi(this);
    ui->channelsWidget->setColumnCount(4);
    ui->channelsWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
    ui->channelsWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Sensitivity (dB)"));
    ui->channelsWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Prism time (us)"));
    ui->channelsWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Gates"));

    ui->tactWidget->setColumnCount(9);
    ui->tactWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Index"));
    ui->tactWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Rx I"));
    ui->tactWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Tx I"));
    ui->tactWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Prog. I"));
    ui->tactWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Freq. I"));
    ui->tactWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("Rx II"));
    ui->tactWidget->setHorizontalHeaderItem(6,new QTableWidgetItem("Tx II"));
    ui->tactWidget->setHorizontalHeaderItem(7,new QTableWidgetItem("Prog. II"));
    ui->tactWidget->setHorizontalHeaderItem(8,new QTableWidgetItem("Freq. II"));

    ui->tactWidget->setColumnWidth(0,50);
    ui->tactWidget->setColumnWidth(1,50);
    ui->tactWidget->setColumnWidth(2,50);
    ui->tactWidget->setColumnWidth(3,50);
    ui->tactWidget->setColumnWidth(4,50);
    ui->tactWidget->setColumnWidth(5,50);
    ui->tactWidget->setColumnWidth(6,50);
    ui->tactWidget->setColumnWidth(7,50);
    ui->tactWidget->setColumnWidth(8,50);
}

ChannelsView::~ChannelsView()
{
    delete ui;
}

void ChannelsView::init(DeviceCalibration *snapshot)
{
    std::vector<Channel*> channels = snapshot->getChannels();


    for(int i=0; i<channels.size(); i++) {
        QTableWidgetItem * item = new ChannelsTableItem("Chan #" + QString::number(i),Qt::red);
        ui->channelsWidget->setItem(i,0,item);
        item = new QTableWidgetItem(QString::number(channels[i]->baseSensLevel()));
        ui->channelsWidget->setItem(i,1,item);
        item = new QTableWidgetItem(QString::number(channels[i]->prismTime()));
        ui->channelsWidget->setItem(i,2,item);
        item = new QTableWidgetItem(QString::number(channels[i]->gates().size()));
        ui->channelsWidget->setItem(i,3,item);
    }

    std::vector<Tact*> tacts = snapshot->getTactTable();
    qDebug() << "Size:" <<tacts.size();
    for(int i=0; i<tacts.size(); i++) {
        QTableWidgetItem * item = new QTableWidgetItem("#" + QString::number(i));
        ui->tactWidget->setItem(i,0,item);
        item = new QTableWidgetItem(QString::number(tacts.at(i)->getRx1()));
        ui->tactWidget->setItem(i,1,item);
        item = new QTableWidgetItem(QString::number(tacts.at(i)->getTx1()));
        ui->tactWidget->setItem(i,2,item);
        item = new QTableWidgetItem(QString::number(tacts.at(i)->getProg1()));
        ui->tactWidget->setItem(i,3,item);
        item = new QTableWidgetItem(QString::number(tacts.at(i)->getFreq1()));
        ui->tactWidget->setItem(i,4,item);
        item = new QTableWidgetItem(QString::number(tacts.at(i)->getRx2()));
        ui->tactWidget->setItem(i,5,item);
        item = new QTableWidgetItem(QString::number(tacts.at(i)->getTx2()));
        ui->tactWidget->setItem(i,6,item);
        item = new QTableWidgetItem(QString::number(tacts.at(i)->getProg2()));
        ui->tactWidget->setItem(i,7,item);
        item = new QTableWidgetItem(QString::number(tacts.at(i)->getFreq2()));
        ui->tactWidget->setItem(i,8,item);
    }

    update();
}
