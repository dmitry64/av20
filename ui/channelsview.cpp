#include "channelsview.h"
#include "ui_channelsview.h"
#include <QTableWidgetItem>
#include <QDebug>
#include <QScrollBar>
#include "controls/widescrollbar.h"

void ChannelsView::initChannelsWidget()
{
    ui->channelsWidget->setColumnCount(8);
    ui->channelsWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(tr("Physical\nChannel")));
    ui->channelsWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(tr("Active")));
    ui->channelsWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(tr("Angle")));
    ui->channelsWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("\u0394t"));
    ui->channelsWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(tr("Gates")));
    ui->channelsWidget->setHorizontalHeaderItem(5,new QTableWidgetItem("X2"));
    ui->channelsWidget->setHorizontalHeaderItem(6,new QTableWidgetItem(tr("Freqency")));
    ui->channelsWidget->setHorizontalHeaderItem(7,new QTableWidgetItem(tr("Pulse\nprog")));

    ui->channelsWidget->setColumnWidth(0,90);
    ui->channelsWidget->setColumnWidth(1,60);
    ui->channelsWidget->setColumnWidth(2,60);
    ui->channelsWidget->setColumnWidth(3,60);
    ui->channelsWidget->setColumnWidth(4,150);
    ui->channelsWidget->setColumnWidth(5,60);
    ui->channelsWidget->setColumnWidth(6,80);
    ui->channelsWidget->setColumnWidth(7,80);

    WideScrollBar * sb = new WideScrollBar();
    ui->channelsWidget->setVerticalScrollBar(sb);

    ui->channelsWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void ChannelsView::initTactWidget()
{
    ui->tactWidget->setColumnCount(5);
    ui->tactWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(tr("Index")));
    ui->tactWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(tr("Rx I")));
    ui->tactWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(tr("Tx I")));
    ui->tactWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(tr("Rx II")));
    ui->tactWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(tr("Tx II")));

    ui->tactWidget->setColumnWidth(0,50);
    ui->tactWidget->setColumnWidth(1,60);
    ui->tactWidget->setColumnWidth(2,60);
    ui->tactWidget->setColumnWidth(3,60);
    ui->tactWidget->setColumnWidth(4,60);
}

ChannelsView::ChannelsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelsView)
{
    ui->setupUi(this);
    _core = 0;
    initChannelsWidget();

    initTactWidget();
    _disabledChannelsColor = QColor(60,60,60);
}

ChannelsView::~ChannelsView()
{
    delete ui;
}

void ChannelsView::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        initChannelsWidget();
        initTactWidget();

        init();
    }
    QWidget::changeEvent(event);
}

void ChannelsView::init()
{
    Q_ASSERT(_core);
    const ChannelsCalibration & calibration =  _core->getCalibrationsSnapshot();
    const TactTable & tactTable = _core->getTactTableSnapshot();
    init(calibration,tactTable);
}

void ChannelsView::fillTactsTable(const std::vector<Tact>& tacts, const ChannelsCalibration& calibrationsSnapshot)
{
    const size_t tactsSize= tacts.size();
    for(size_t i=0; i<tactsSize; i++) {
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
                item->setBackgroundColor(_disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,1,item);
            item = new QTableWidgetItem(QString::number(tact.getTx1()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact.getTx1Enabled()) {
                const Channel & chan = calibrationsSnapshot.getChannel(tact.getTx1());
                item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            }
            else {
                item->setBackgroundColor(_disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,2,item);

            item = new QTableWidgetItem(QString::number(tact.getRx2()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact.getRx2Enabled()) {
                const Channel & chan = calibrationsSnapshot.getChannel(tact.getRx2());
                item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            }
            else {
                item->setBackgroundColor(_disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,3,item);
            item = new QTableWidgetItem(QString::number(tact.getTx2()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );

            if(tact.getTx2Enabled()) {
                const Channel & chan = calibrationsSnapshot.getChannel(tact.getTx2());
                item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            }
            else {
                item->setBackgroundColor(_disabledChannelsColor);
            }
            ui->tactWidget->setItem(i,4,item);
        }
    }
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
            QTableWidgetItem * item = new QTableWidgetItem(tr("Chan #") + QString::number(i));
            item->setBackgroundColor(QColor(chan.getColorRed(),chan.getColorGreen(),chan.getColorBlue()));
            ui->channelsWidget->setItem(channelsRow,0,item);
            item = new QTableWidgetItem((chan.getActiveDisplayChannelIndex() == j) ? tr("yes") : tr("no"));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,1,item);
            item = new QTableWidgetItem(QString::number(disp.angle()));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,2,item);
            item = new QTableWidgetItem(QString::number(rxchan.getPrismTime()) + QString(tr(" us")));
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
            item = new QTableWidgetItem(QString((txchan.doubleMode()) ? tr("yes") : tr("no")));
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,5,item);
            item = new QTableWidgetItem(FreqStrings[txchan.freq()]);
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,6,item);
            item = new QTableWidgetItem(ProgStrings[txchan.prog()]);
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignCenter );
            ui->channelsWidget->setItem(channelsRow,7,item);

            channelsRow++;
            ui->channelsWidget->setRowCount(channelsRow+1);
        }
    }
    ui->channelsWidget->setRowCount(channelsRow);
    ui->channelsWidget->resizeRowsToContents();


    const std::vector<Tact> & tacts = tactTableSnapshot.getTactTable();
    fillTactsTable(tacts, calibrationsSnapshot);

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
