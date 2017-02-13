#include "debuggui.h"
#include "ui_debuggui.h"
#include <QDebug>
#include "device/channel.h"

DebugGUI::DebugGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugGUI)
{
    ui->setupUi(this);
    _core = 0;
    //connect(this,SIGNAL(AScanSingle(AScan)),ui->ascanWidgetSingle,SLOT(onAScan(AScan)));
    //connect(this,SIGNAL(AScanAB(QSharedPointer<AScanDrawData>)),ui->aScanPage,SLOT(onAScan(QSharedPointer<AScanDrawData>)));
    //connect(this,SIGNAL(BScanAB(QSharedPointer<BScanDrawData>)),ui->aScanPage,SLOT(onBScan(QSharedPointer<BScanDrawData>)));
    //connect(this,SIGNAL(AScanAB(AScan)),ui->aScanPage,SLOT(onAScan(AScan)));
    //connect(this,SIGNAL(AScanSingle(AScan)),ui->aScanPage,SLOT(onAScan(AScan)));
    //connect(this,SIGNAL(AScanSingle(AScan)),ui->bscanWidgetSingle,SLOT(onAScan(AScan)));
    //connect(this,SIGNAL(BScanAB(QSharedPointer<BScanDrawData>)), ui->bscan8,SLOT(onBScan(QSharedPointer<BScanDrawData>)));

    connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), ui->aScanPage,SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));
    connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), ui->bscan8,SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));

    connect(this,SIGNAL(channelChanged(Channel)),ui->aScanPage,SLOT(onChannelChanged(Channel)));

    //connect(this,SIGNAL(TVGReady(TVG)),ui->ascanWidgetSingle,SLOT(onTVG(TVG)));
    //connect(this,SIGNAL(TVGReady(TVG)),ui->aScanPage,SLOT(onTVG(TVG)));
}

DebugGUI::~DebugGUI()
{
    delete ui;
}

void DebugGUI::setCore(Core *core)
{
    _core = core;

    ui->aScanPage->setCore(core);
    ui->channelsWidget->setCore(core);
}

AScanWidget *DebugGUI::getAscanWidgetSingle()
{
    return ui->ascanWidgetSingle;
}

void DebugGUI::init()
{
    if(_core!=0) {
        DeviceCalibration * calibration = _core->getSnapshot();
        ui->aScanPage->onTVG(calibration->getChannel(0)->generateTVG());
        ui->aScanPage->init(0,calibration);

        std::vector<Channel*> channels = calibration->getChannels();
        std::vector< std::vector<Channel> > channelsTable;
        for(int i=0; i<channels.size(); i++) {
            std::vector<Channel> channelsForTape;
            channelsForTape.push_back(*(channels[i]));
            channelsTable.push_back(channelsForTape);
        }
        ui->bscan8->setChannles(channelsTable);

        ui->channelsWidget->init(calibration);

        delete calibration;
    }
}

void DebugGUI::showEvent(QShowEvent *event) {
    QWidget::showEvent( event );
    init();
}

void DebugGUI::debug(int value)
{
    ui->progressBar->setValue(value % 100);
}

void DebugGUI::onConnectionStatusChanged(bool status)
{
    ui->connectionCheckBox->setChecked(status);
}

void DebugGUI::onErrorStatusChanged(bool status)
{
    ui->errorCheckBox->setChecked(status);
}

void DebugGUI::onDeviceErrorStatusChanged(bool status)
{
    ui->deviceErrorCheckBox->setChecked(status);
}

void DebugGUI::onDeviceOverheatStatusChanged(bool status)
{
    ui->overheatCheckBox->setChecked(status);
}

void DebugGUI::onDeviceReadyStatusChanged(bool status)
{
    ui->deviceReadyCheckBox->setChecked(status);
}

void DebugGUI::onAScan(QSharedPointer<AScanDrawData> scan)
{
    emit AScanAB(scan);
}

void DebugGUI::onBScan(QSharedPointer<BScanDrawData> scan)
{
    emit BScanAB(scan);
}

void DebugGUI::onTVG(TVG tvg)
{
    emit TVGReady(tvg);
}

void DebugGUI::onChannelChanged(Channel channel)
{
    emit channelChanged(channel);
}

void DebugGUI::onDisplayPackage(QSharedPointer<DisplayPackage> dp)
{
    emit drawDisplayPackage(dp);
}

/*void DebugGUI::onChannelChanged(uint8_t channel)
{
    ui->controlPanel->setChannel(channel);
    init();
}*/

void DebugGUI::on_exitButton_released()
{
    QApplication::exit(0);
}

void DebugGUI::on_pushButton_2_released()
{

}

void DebugGUI::on_tabWidget_currentChanged(int index)
{
    qDebug() << "Tab selected:"<<index;
    switch (index) {
    case 0:
    case 1:
    case 2:
        _core->setDeviceMode(DEVICE_MODE_EVAL);
        break;
    case 3:
        _core->setDeviceMode(DEVICE_MODE_SEARCH);
        break;
    default:
        break;
    }
}
