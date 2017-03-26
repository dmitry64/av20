#include "channelsview.h"
#include "ui_channelsview.h"
#include <QTableWidgetItem>
#include <QDebug>
#include <QScrollBar>

ChannelsView::ChannelsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelsView)
{
    ui->setupUi(this);
    _core = 0;
    ui->channelsWidget->setColumnCount(8);
    ui->channelsWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Physical\nChannel"));
    ui->channelsWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Active"));
    ui->channelsWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Angle"));
    ui->channelsWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("\u0394t"));
    ui->channelsWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Gates"));
    ui->channelsWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("X2"));
    ui->channelsWidget->setHorizontalHeaderItem(6,new QTableWidgetItem("Freqency"));
    ui->channelsWidget->setHorizontalHeaderItem(7,new QTableWidgetItem("Pulse\nprog"));

    ui->channelsWidget->setColumnWidth(0,70);
    ui->channelsWidget->setColumnWidth(1,50);
    ui->channelsWidget->setColumnWidth(2,50);
    ui->channelsWidget->setColumnWidth(3,50);
    ui->channelsWidget->setColumnWidth(4,120);
    ui->channelsWidget->setColumnWidth(5,60);
    ui->channelsWidget->setColumnWidth(6,60);
    ui->channelsWidget->setColumnWidth(7,60);

    ui->tactWidget->setColumnCount(5);
    ui->tactWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Index"));
    ui->tactWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Rx I"));
    ui->tactWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Tx I"));
    ui->tactWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Rx II"));
    ui->tactWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Tx II"));

    ui->tactWidget->setColumnWidth(0,50);
    ui->tactWidget->setColumnWidth(1,40);
    ui->tactWidget->setColumnWidth(2,40);
    ui->tactWidget->setColumnWidth(3,40);
    ui->tactWidget->setColumnWidth(4,40);
}

ChannelsView::~ChannelsView()
{
    delete ui;
}

void ChannelsView::init()
{
    Q_ASSERT(_core);
    const ChannelsCalibration & calibration =  _core->getCalibrationsSnapshot();
    const TactTable & tactTable = _core->getTactTableSnapshot();
    init(calibration,tactTable);
}

void ChannelsView::init(const ChannelsCalibration & calibrationsSnapshot, const TactTable & tactTableSnapshot)
{
    logEvent("ChannelsView","Initializing");
    Q_ASSERT(_core);
    ui->channelsWidget->clearContents();
    ui->tactWidget->clearContents();
    int channelsRow = 0;
    for(uint8_t i=0; i<calibrationsSnapshot.getChannelsCount(); i++) {
        const Channel & chan = calibrationsSnapshot.getChannel(i);
        const auto & dispChannels = chan.getDisplayChannels();
        for(uint8_t j=0; j<dispChannels.size(); j++) {
            const DisplayChannel & disp = dispChannels.at(j);
            const RxChannel & rxchan = disp.getRx();
            QTableWidgetItem * item = new QTableWidgetItem("Chan #" + QString::number(i));
            item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            ui->channelsWidget->setItem(channelsRow,0,item);
            item = new QTableWidgetItem((chan.getActiveDisplayChannelIndex() == j) ? "yes" : "no");
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,1,item);
            item = new QTableWidgetItem(QString::number(disp.angle()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,2,item);
            item = new QTableWidgetItem(QString::number(rxchan.getPrismTime()) + QString(" us"));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,3,item);
            const std::vector<Gate> & gates = disp.gates();
            QString gatesString;
            for(size_t j=0; j<gates.size(); j++) {
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
            ui->channelsWidget->setItem(channelsRow,4,item);

            const TxChannel & txchan = disp.getTx();
            item = new QTableWidgetItem(QString((txchan.doubleMode()) ? "yes" : "no"));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,5,item);
            item = new QTableWidgetItem(QString(FreqStrings[txchan.freq()].c_str()) + QString(" MHz"));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,6,item);
            item = new QTableWidgetItem(QString(ProgStrings[txchan.prog()].c_str()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,7,item);

            channelsRow++;
            ui->channelsWidget->setRowCount(channelsRow+1);
        }
    }
    ui->channelsWidget->setRowCount(channelsRow);
    ui->channelsWidget->resizeRowsToContents();
    QColor disabledChannelsColor = QColor(60,60,60);

    const std::vector<Tact> & tacts = tactTableSnapshot.getTactTable();

    for(size_t i=0; i<tacts.size(); i++) {
        const Tact & tact = tacts.at(i);
        if(tact.getTactEnabled()) {
            QTableWidgetItem * item = new QTableWidgetItem("#" + QString::number(i));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->tactWidget->setItem(i,0,item);
            item = new QTableWidgetItem(QString::number(tact.getRx1()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact.getRx1Enabled()) {
                const Channel & chan = calibrationsSnapshot.getChannel(tact.getRx1());
                item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            }
            else {
                item->setBackgroundColor(disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,1,item);
            item = new QTableWidgetItem(QString::number(tact.getTx1()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact.getTx1Enabled()) {
                const Channel & chan = calibrationsSnapshot.getChannel(tact.getTx1());
                item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            }
            else {
                item->setBackgroundColor(disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,2,item);

            item = new QTableWidgetItem(QString::number(tact.getRx2()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact.getRx2Enabled()) {
                const Channel & chan = calibrationsSnapshot.getChannel(tact.getRx2());
                item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            }
            else {
                item->setBackgroundColor(disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,3,item);
            item = new QTableWidgetItem(QString::number(tact.getTx2()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact.getTx2Enabled()) {
                const Channel & chan = calibrationsSnapshot.getChannel(tact.getTx2());
                item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            }
            else {
                item->setBackgroundColor(disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,4,item);
        }
    }

    update();
}

void ChannelsView::setCore(Core *core)
{
    Q_ASSERT(core);
    _core = core;
}

void ChannelsView::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    init();
}
