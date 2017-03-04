#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _backgroundWidget = new QPushButton(ui->centralTabWidget);
    _backgroundWidget->setFlat(true);
    _backgroundWidget->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Button, QColor(100,100,100,200));
    _backgroundWidget->setPalette(palette);
    _backgroundWidget->setGeometry(0,0,2048,2048);
    _backgroundWidget->hide();
    connect(_backgroundWidget,SIGNAL(pressed()),ui->menuWidget,SLOT(resetMenu()));

    _helpWidget = new HelpWidget(ui->centralTabWidget);
    _helpWidget->hide();

    _modeSelectionWidget = new ModeSelectionWidget(ui->centralTabWidget);
    _modeSelectionWidget->hide();

    _calibrationsWidget = new CalibrationsWidget(ui->centralTabWidget);
    _calibrationsWidget->hide();

    _registrationWidget = new RegistrationWidget(ui->centralTabWidget);
    _registrationWidget->hide();

    _memoryWidget = new MemoryWidget(ui->centralTabWidget);
    _memoryWidget->hide();

    _optionsWidget = new OptionsWidget(ui->centralTabWidget);
    _optionsWidget->hide();

    _systemWidget = new SystemWidget(ui->centralTabWidget);
    _systemWidget->hide();

    connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), ui->aScanPage,SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));
    connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), ui->bScanPage,SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));
    connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), ui->tvgEditorWidget,SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));

    connect(this,SIGNAL(channelChanged(Channel*)),ui->aScanPage,SLOT(onChannelChanged(Channel*)));
    connect(this,SIGNAL(channelChanged(Channel*)),ui->bScanPage,SLOT(onChannelChanged(Channel*)));
    connect(this,SIGNAL(channelChanged(Channel*)),ui->tvgEditorWidget,SLOT(onChannelChanged(Channel*)));

    connect(this,SIGNAL(resetMenu()),ui->menuWidget,SLOT(resetMenu()));

    connect(ui->menuWidget,SIGNAL(helpMenuOpened()),this,SLOT(onHelpMenuOpened()));
    connect(ui->menuWidget,SIGNAL(helpMenuClosed()),this,SLOT(onHelpMenuClosed()));
    connect(ui->menuWidget,SIGNAL(modeMenuOpened()),this,SLOT(onModeMenuOpened()));
    connect(ui->menuWidget,SIGNAL(modeMenuClosed()),this,SLOT(onModeMenuClosed()));
    connect(ui->menuWidget,SIGNAL(calibrationsMenuOpened()),this,SLOT(onCalibrationsMenuOpened()));
    connect(ui->menuWidget,SIGNAL(calibrationsMenuClosed()),this,SLOT(onCalibrationsMenuClosed()));
    connect(ui->menuWidget,SIGNAL(registrationMenuOpened()),this,SLOT(onRegistrationMenuOpened()));
    connect(ui->menuWidget,SIGNAL(registrationMenuClosed()),this,SLOT(onRegistrationMenuClosed()));
    connect(ui->menuWidget,SIGNAL(memoryMenuOpened()),this,SLOT(onMemoryMenuOpened()));
    connect(ui->menuWidget,SIGNAL(memoryMenuClosed()),this,SLOT(onMemoryMenuClosed()));
    connect(ui->menuWidget,SIGNAL(optionsMenuOpened()),this,SLOT(onOptionsMenuOpened()));
    connect(ui->menuWidget,SIGNAL(optionsMenuClosed()),this,SLOT(onOptionsMenuClosed()));
    connect(ui->menuWidget,SIGNAL(systemMenuOpened()),this,SLOT(onSystemMenuOpened()));
    connect(ui->menuWidget,SIGNAL(systemMenuClosed()),this,SLOT(onSystemMenuClosed()));

    connect(_systemWidget,SIGNAL(shutdown()),this,SLOT(onShutdown()));
    connect(_systemWidget,SIGNAL(reboot()),this,SLOT(onReboot()));
    connect(_systemWidget,SIGNAL(pause()),this,SLOT(onPause()));

    connect(_modeSelectionWidget,SIGNAL(modeSelected(uint8_t,uint8_t)),this,SLOT(onModeChangeRequested(uint8_t,uint8_t)));
    connect(_modeSelectionWidget,SIGNAL(closeWindow()),this,SIGNAL(resetMenu()));
    connect(_calibrationsWidget,SIGNAL(calibrationSelected()),this,SIGNAL(resetMenu()));

}

MainWindow::~MainWindow()
{
    qDebug() << "Destoying main window";
    delete _backgroundWidget;
    delete _calibrationsWidget;
    delete _helpWidget;
    delete _memoryWidget;
    delete _modeSelectionWidget;
    delete _optionsWidget;
    delete _registrationWidget;
    delete _systemWidget;
    delete ui;
}

void MainWindow::setCore(Core *core)
{
    _core = core;

    ui->aScanPage->setCore(core);
    ui->bScanPage->setCore(core);
    ui->tvgEditorWidget->setCore(core);
    ui->channelsWidget->setCore(core);
    _modeSelectionWidget->setCore(core);
    _modeSelectionWidget->init();
    _calibrationsWidget->setCore(core);
}

void MainWindow::onChannelChanged(Channel *channel)
{
    emit channelChanged(channel);
}

void MainWindow::onDisplayPackage(QSharedPointer<DisplayPackage> dp)
{
    emit drawDisplayPackage(dp);
}

void MainWindow::onModeChangeRequested(uint8_t modeIndex, uint8_t tableIndex)
{
    reset();
    _core->setDeviceMode(modeIndex,tableIndex);
    //init();
}

void MainWindow::onModeChanged()
{
    init();
}

void MainWindow::onCalibrationChanged()
{
    init();
}

void MainWindow::onHelpMenuOpened()
{
    _helpWidget->setGeometry(ui->centralTabWidget->width()/2 - 800/2,ui->centralTabWidget->height()/2 - 400/2, 800, 400);
    _backgroundWidget->show();
    _helpWidget->show();
}

void MainWindow::onHelpMenuClosed()
{
    _helpWidget->hide();
    _backgroundWidget->hide();
}

void MainWindow::onModeMenuOpened()
{
    _modeSelectionWidget->setGeometry(ui->centralTabWidget->width()/2 - 800/2,ui->centralTabWidget->height()/2 - 400/2, 800, 400);
    _backgroundWidget->show();
    _modeSelectionWidget->show();
}

void MainWindow::onModeMenuClosed()
{
    _backgroundWidget->hide();
    _modeSelectionWidget->hide();
}

void MainWindow::onCalibrationsMenuOpened()
{
    _calibrationsWidget->setGeometry(ui->centralTabWidget->width()/2 - 800/2,ui->centralTabWidget->height()/2 - 400/2, 800, 400);
    _backgroundWidget->show();
    _calibrationsWidget->show();
}

void MainWindow::onCalibrationsMenuClosed()
{
    _backgroundWidget->hide();
    _calibrationsWidget->hide();
}

void MainWindow::onRegistrationMenuOpened()
{
    _registrationWidget->setGeometry(ui->centralTabWidget->width()/2 - 800/2,ui->centralTabWidget->height()/2 - 400/2, 800, 400);
    _registrationWidget->show();
    _backgroundWidget->show();
}

void MainWindow::onRegistrationMenuClosed()
{
    _registrationWidget->hide();
    _backgroundWidget->hide();
}

void MainWindow::onMemoryMenuOpened()
{
    _memoryWidget->setGeometry(ui->centralTabWidget->width()/2 - 800/2,ui->centralTabWidget->height()/2 - 400/2, 800, 400);
    _memoryWidget->show();
    _backgroundWidget->show();
}

void MainWindow::onMemoryMenuClosed()
{
    _memoryWidget->hide();
    _backgroundWidget->hide();
}

void MainWindow::onOptionsMenuOpened()
{
    _optionsWidget->setGeometry(ui->centralTabWidget->width()/2 - 800/2,ui->centralTabWidget->height()/2 - 400/2, 800, 400);
    _optionsWidget->show();
    _backgroundWidget->show();
}

void MainWindow::onOptionsMenuClosed()
{
    _optionsWidget->hide();
    _backgroundWidget->hide();
}

void MainWindow::onSystemMenuOpened()
{
    _systemWidget->setGeometry(ui->centralTabWidget->width()/2 - 800/2,ui->centralTabWidget->height()/2 - 400/2, 800, 400);
    _systemWidget->show();
    _backgroundWidget->show();
}

void MainWindow::onSystemMenuClosed()
{
    _systemWidget->hide();
    _backgroundWidget->hide();
}

void MainWindow::onDeviceOverheatEnable()
{
    ui->statusWidget->onDeviceOverheatEnabled();
}

void MainWindow::onDeviceOverheatDisable()
{
    ui->statusWidget->onDeviceOverheatDisabled();
}

void MainWindow::onDeviceErrorEnable()
{
    ui->statusWidget->onDeviceErrorEnabled();
}

void MainWindow::onDeviceErrorDisable()
{
    ui->statusWidget->onDeviceErrorDisabled();
}

void MainWindow::onDeviceConnectionErrorEnable()
{
    ui->statusWidget->onDeviceConnectionErrorEnabled();
}

void MainWindow::onDeviceConnectionErrorDisable()
{
    ui->statusWidget->onDeviceConnectionErrorDisabled();
}

void MainWindow::onShutdown()
{
    _core->stopCore();
    QApplication::exit(0);
}

void MainWindow::onReboot()
{
    _core->stopCore();
    QApplication::exit(0);
}

void MainWindow::onPause()
{

}

void MainWindow::init()
{
    ui->statusWidget->init();
    Q_ASSERT(_core);
    const ChannelsCalibration & calibration = _core->getCalibrationsSnapshot();
    const TactTable & tactTableSnapshot = _core->getTactTableSnapshot();

    ui->aScanPage->init(0,calibration);
    ui->tvgEditorWidget->init(0,calibration);
    /*
        std::vector< std::vector<Channel*> > channelsTable;
        for(int i=0; i<calibration->getChannelsCount(); i++) {
            std::vector<Channel*> channelsForTape;
            channelsForTape.push_back(calibration->getChannel(i));
            channelsTable.push_back(channelsForTape);
        }
        ui->bScanPage->setChannles(channelsTable);
        ui->bScanPage->init(calibration);

        ui->channelsWidget->init(calibration,tactTableSnapshot);

        _calibrationsWidget->init(calibration);*/


}

void MainWindow::reset()
{
    Q_ASSERT(_core);
    ui->aScanPage->reset();
    ui->tvgEditorWidget->reset();
    ui->bScanPage->reset();
}
