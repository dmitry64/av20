#include "channelsview.h"
#include "ui_channelsview.h"
#include <QTableWidgetItem>
#include <QDebug>

ChannelsView::ChannelsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelsView)
{
    ui->setupUi(this);
    _core = 0;
    ui->channelsWidget->setColumnCount(6);
    ui->channelsWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Name"));
    ui->channelsWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Angle"));
    ui->channelsWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Prism time (us)"));
    ui->channelsWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Gates"));
    ui->channelsWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Freq (MHz)"));
    ui->channelsWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("Prog #"));

    ui->channelsWidget->setColumnWidth(0,70);
    ui->channelsWidget->setColumnWidth(1,50);

    ui->tactWidget->setColumnCount(5);
    ui->tactWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Index"));
    ui->tactWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Rx I"));
    ui->tactWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Tx I"));
//    ui->tactWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Prog. I"));
//    ui->tactWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Freq. I"));
    ui->tactWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Rx II"));
    ui->tactWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Tx II"));
//    ui->tactWidget->setHorizontalHeaderItem(7,new QTableWidgetItem("Prog. II"));
//    ui->tactWidget->setHorizontalHeaderItem(8,new QTableWidgetItem("Freq. II"));

    ui->tactWidget->setColumnWidth(0,50);
    ui->tactWidget->setColumnWidth(1,50);
    ui->tactWidget->setColumnWidth(2,50);
    ui->tactWidget->setColumnWidth(3,50);
    ui->tactWidget->setColumnWidth(4,50);
}

ChannelsView::~ChannelsView()
{
    delete ui;
}

void ChannelsView::init()
{
    Q_ASSERT(_core);
    ChannelsCalibration * calibration =  _core->getCalibrationsSnapshot();
    TactTable * tactTable = _core->getTactTableSnapshot();
    init(calibration,tactTable);
    delete calibration;
    delete tactTable;
}

void ChannelsView::init(ChannelsCalibration *calibrationsSnapshot, TactTable * tactTableSnapshot)
{
    Q_ASSERT(calibrationsSnapshot);
    Q_ASSERT(tactTableSnapshot);
    Q_ASSERT(_core);
    ui->channelsWidget->clearContents();
    ui->tactWidget->clearContents();

    for(int i=0; i<calibrationsSnapshot->getChannelsCount(); i++) {
        Channel * chan = calibrationsSnapshot->getChannel(i);
        RxChannel * rxchan = chan->rx();
        QTableWidgetItem * item = new QTableWidgetItem("Chan #" + QString::number(i));
        item->setBackgroundColor(QColor(chan->getColorRed(),chan->getColorGreen(),chan->getColorBlue()));
        ui->channelsWidget->setItem(i,0,item);
        item = new QTableWidgetItem(QString(rxchan->getName().c_str()));
        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
        ui->channelsWidget->setItem(i,1,item);
        item = new QTableWidgetItem(QString::number(rxchan->getPrismTime()));
        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
        ui->channelsWidget->setItem(i,2,item);
        std::vector<Gate> gates = rxchan->gates();
        QString gatesString;
        for(int j=0; j<gates.size(); j++) {
            Gate gate = gates.at(j);
            if(j!=0) {
                gatesString+="\n";
            }
            gatesString+=QString::number(gate._start) +
                   "-" + QString::number(gate._finish) +
                   " [" + QString::number(gate._level) + "]";

        }
        item = new QTableWidgetItem(gatesString);
        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
        ui->channelsWidget->setItem(i,3,item);
        item = new QTableWidgetItem(QString(FreqStrings[chan->tx()->freq()].c_str()));
        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
        ui->channelsWidget->setItem(i,4,item);
        item = new QTableWidgetItem(QString(ProgStrings[chan->tx()->prog()].c_str()));
        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
        ui->channelsWidget->setItem(i,5,item);

    }
    QColor disabledChannelsColor = QColor(60,60,60);

    std::vector<Tact*> tacts = tactTableSnapshot->getTactTable();

    for(int i=0; i<tacts.size(); i++) {
        Tact * tact = tacts.at(i);
        if(tact->getTactEnabled()) {
            QTableWidgetItem * item = new QTableWidgetItem("#" + QString::number(i));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->tactWidget->setItem(i,0,item);
            item = new QTableWidgetItem(QString::number(tact->getRx1()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact->getRx1Enabled()) {
                Channel * chan = calibrationsSnapshot->getChannel(tact->getRx1());
                item->setBackgroundColor(QColor(chan->getColorRed(),chan->getColorGreen(),chan->getColorBlue()));
            } else {
                item->setBackgroundColor(disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,1,item);
            item = new QTableWidgetItem(QString::number(tact->getTx1()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact->getTx1Enabled()) {
                Channel * chan = calibrationsSnapshot->getChannel(tact->getTx1());
                item->setBackgroundColor(QColor(chan->getColorRed(),chan->getColorGreen(),chan->getColorBlue()));
            } else {
                item->setBackgroundColor(disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,2,item);
            /*item = new QTableWidgetItem(QString(ProgStrings[calibrationsSnapshot->getChannel(tact->getTx1())->tx()->prog()].c_str()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->tactWidget->setItem(i,3,item);
            item = new QTableWidgetItem(QString(FreqStrings[calibrationsSnapshot->getChannel(tact->getTx1())->tx()->freq()].c_str()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->tactWidget->setItem(i,4,item);*/
            item = new QTableWidgetItem(QString::number(tact->getRx2()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact->getRx2Enabled()) {
                Channel * chan = calibrationsSnapshot->getChannel(tact->getRx2());
                item->setBackgroundColor(QColor(chan->getColorRed(),chan->getColorGreen(),chan->getColorBlue()));
            } else {
                item->setBackgroundColor(disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,3,item);
            item = new QTableWidgetItem(QString::number(tact->getTx2()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact->getTx2Enabled()) {
                Channel * chan = calibrationsSnapshot->getChannel(tact->getTx2());
                item->setBackgroundColor(QColor(chan->getColorRed(),chan->getColorGreen(),chan->getColorBlue()));
            } else {
                item->setBackgroundColor(disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,4,item);
            /*
            item = new QTableWidgetItem(QString(ProgStrings[calibrationsSnapshot->getChannel(tact->getTx2())->tx()->prog()].c_str()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->tactWidget->setItem(i,7,item);
            item = new QTableWidgetItem(QString(FreqStrings[calibrationsSnapshot->getChannel(tact->getTx2())->tx()->freq()].c_str()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->tactWidget->setItem(i,8,item);*/
        }
    }

    update();
}

void ChannelsView::setCore(Core *core)
{
    _core = core;
}

void ChannelsView::showEvent(QShowEvent *event)
{
    init();
}
