#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    _backgroundWidget->setGeometry(0,0,1024,800);
    _backgroundWidget->hide();
    connect(_backgroundWidget,SIGNAL(pressed()),ui->menuWidget,SLOT(resetMenu()));

    _helpWidget = new HelpWidget(ui->centralTabWidget);
    _helpWidget->hide();

    _modeSelectionWidget = new ModeSelectionWidget(ui->centralTabWidget);
    _modeSelectionWidget->hide();

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

    connect(this,SIGNAL(channelChanged(Channel)),ui->aScanPage,SLOT(onChannelChanged(Channel)));
    connect(this,SIGNAL(channelChanged(Channel)),ui->bScanPage,SLOT(onChannelChanged(Channel)));
    connect(this,SIGNAL(channelChanged(Channel)),ui->tvgEditorWidget,SLOT(onChannelChanged(Channel)));

    connect(ui->menuWidget,SIGNAL(helpMenuOpened()),this,SLOT(onHelpMenuOpened()));
    connect(ui->menuWidget,SIGNAL(helpMenuClosed()),this,SLOT(onHelpMenuClosed()));
    connect(ui->menuWidget,SIGNAL(modeMenuOpened()),this,SLOT(onModeMenuOpened()));
    connect(ui->menuWidget,SIGNAL(modeMenuClosed()),this,SLOT(onModeMenuClosed()));
    connect(ui->menuWidget,SIGNAL(registrationMenuOpened()),this,SLOT(onRegistrationMenuOpened()));
    connect(ui->menuWidget,SIGNAL(registrationMenuClosed()),this,SLOT(onRegistrationMenuClosed()));
    connect(ui->menuWidget,SIGNAL(memoryMenuOpened()),this,SLOT(onMemoryMenuOpened()));
    connect(ui->menuWidget,SIGNAL(memoryMenuClosed()),this,SLOT(onMemoryMenuClosed()));
    connect(ui->menuWidget,SIGNAL(optionsMenuOpened()),this,SLOT(onOptionsMenuOpened()));
    connect(ui->menuWidget,SIGNAL(optionsMenuClosed()),this,SLOT(onOptionsMenuClosed()));
    connect(ui->menuWidget,SIGNAL(systemMenuOpened()),this,SLOT(onSystemMenuOpened()));
    connect(ui->menuWidget,SIGNAL(systemMenuClosed()),this,SLOT(onSystemMenuClosed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCore(Core *core)
{
    _core = core;

    ui->aScanPage->setCore(core);
    ui->bScanPage->setCore(core);
    ui->tvgEditorWidget->setCore(core);
    ui->channelsWidget->setCore(core);
}

void MainWindow::showEvent(QShowEvent *event)
{
    init();
}

void MainWindow::onChannelChanged(Channel channel)
{
    emit channelChanged(channel);
}

void MainWindow::onDisplayPackage(QSharedPointer<DisplayPackage> dp)
{
    emit drawDisplayPackage(dp);
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
    _modeSelectionWidget->setGeometry((ui->centralTabWidget->width()/6) ,ui->centralTabWidget->height() - 220, ui->centralTabWidget->width()/6, 220);
    _backgroundWidget->show();
    _modeSelectionWidget->show();
}

void MainWindow::onModeMenuClosed()
{
    _backgroundWidget->hide();
    _modeSelectionWidget->hide();
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

void MainWindow::init()
{
    ui->statusWidget->init();
    if(_core!=0) {
        DeviceCalibration * calibration = _core->getSnapshot();

        //ui->aScanPage->onTVG(calibration->getChannel(0)->generateTVG());
        ui->aScanPage->init(0,calibration);
        ui->tvgEditorWidget->init(0,calibration);

        std::vector<Channel*> channels = calibration->getChannels();
        std::vector< std::vector<Channel> > channelsTable;
        for(int i=0; i<channels.size(); i++) {
            std::vector<Channel> channelsForTape;
            channelsForTape.push_back(*(channels[i]));
            channelsTable.push_back(channelsForTape);
        }
        ui->bScanPage->setChannles(channelsTable);
        ui->bScanPage->init(calibration);

        ui->channelsWidget->init(calibration);

        delete calibration;
    } else {
        qFatal("Core uninitialized!");
    }
}
