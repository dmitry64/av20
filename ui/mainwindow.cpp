#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCloseEvent>
#include <QWidget>


void MainWindow::closeEvent(QCloseEvent *event)
{
    _core->stopCore();
    QWidget::closeEvent(event);
}

void MainWindow::setColorScheme(UiTheme theme)
{
    switch(theme) {
    case UiTheme::Default:
        this->setPalette(_defaultPalette);
        break;
    case UiTheme::Alternative:
        this->setPalette(_alternativePalette);
        break;
    }
}

void MainWindow::createMenuWidgets()
{
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
}

void MainWindow::generateUiThemes()
{
    _defaultPalette = QWidget::palette();
    _alternativePalette = QWidget::palette();
    _alternativePalette.setColor(QPalette::Window,QColor(30,60,90));
    _alternativePalette.setColor(QPalette::Base,QColor(30,60,90));
    _alternativePalette.setColor(QPalette::AlternateBase,QColor(30,60,90));
    _alternativePalette.setColor(QPalette::Button,QColor(30,60,90));
    _alternativePalette.setColor(QPalette::ButtonText,QColor(200,200,200));
    _alternativePalette.setColor(QPalette::WindowText,QColor(200,200,200));
}

void MainWindow::createBackgroundWidget()
{
    _backgroundWidget = new QPushButton(ui->centralTabWidget);
    _backgroundWidget->setFlat(true);
    _backgroundWidget->setAutoFillBackground(true);
    QPalette backgroundPalette;
    backgroundPalette.setColor(QPalette::Button, QColor(100,100,100,200));
    _backgroundWidget->setPalette(backgroundPalette);
    _backgroundWidget->setGeometry(0,0,2048,2048);
    _backgroundWidget->hide();
}

void MainWindow::connectMenuWidgets()
{
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
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose);

    generateUiThemes();

    this->setColorScheme(System::getInstance()->getSettings()->getGlobalUiTheme());

    createBackgroundWidget();
    connect(_backgroundWidget,SIGNAL(pressed()),ui->menuWidget,SLOT(resetMenu()));

    createMenuWidgets();

    connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), ui->aScanPage,SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));
    connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), ui->bScanPage,SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));
    connect(this,SIGNAL(drawDisplayPackage(QSharedPointer<DisplayPackage>)), ui->tvgEditorWidget,SLOT(onDisplayPackage(QSharedPointer<DisplayPackage>)));

    connect(this,SIGNAL(channelChanged(Channel)),ui->aScanPage,SLOT(onChannelChanged(Channel)));
    connect(this,SIGNAL(channelChanged(Channel)),ui->bScanPage,SLOT(onChannelChanged(Channel)));
    connect(this,SIGNAL(channelChanged(Channel)),ui->tvgEditorWidget,SLOT(onChannelChanged(Channel)));

    connectMenuWidgets();

    connect(_optionsWidget,SIGNAL(colorSchemeChanged(UiTheme)),this,SLOT(setColorScheme(UiTheme)));

    connect(_systemWidget,SIGNAL(shutdown()),this,SLOT(onShutdown()));
    connect(_systemWidget,SIGNAL(reboot()),this,SLOT(onReboot()));
    connect(_systemWidget,SIGNAL(pause()),this,SLOT(onPause()));

    connect(_modeSelectionWidget,SIGNAL(modeSelected(uint8_t,uint8_t)),this,SLOT(onModeChangeRequested(uint8_t,uint8_t)));
    connect(_modeSelectionWidget,SIGNAL(closeWindow()),this,SIGNAL(resetMenu()));
    connect(_calibrationsWidget,SIGNAL(calibrationSelected()),this,SIGNAL(resetMenu()));

    connect(this,SIGNAL(registrationStateChanged(bool)),ui->statusWidget,SLOT(onRegistrationStatusChanged(bool)));
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
    _registrationWidget->setCore(core);
}

void MainWindow::onChannelChanged(Channel channel)
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
    logEvent("MainWindow","Shutdown started...");
    _core->stopCore();
    System::getInstance()->shutdown();
    logEvent("MainWindow","Exit");
    QApplication::exit(0);
}

void MainWindow::onReboot()
{
    logEvent("MainWindow","Reboot started...");
    _core->stopCore();
    System::getInstance()->reboot();
    logEvent("MainWindow","Exit");
    QApplication::exit(0);
}

void MainWindow::onPause()
{
    logEvent("MainWindow","Pause pressed");
}

void MainWindow::init()
{
    ui->statusWidget->init();
    Q_ASSERT(_core);
    const ChannelsCalibration & calibration = _core->getCalibrationsSnapshot();
    const TactTable & tactTableSnapshot = _core->getTactTableSnapshot();

    ChannelsInfo defaultChannel;
    defaultChannel._channel = 0;
    defaultChannel._displayChannel = 0;

    ui->aScanPage->init(defaultChannel,calibration);
    ui->tvgEditorWidget->init(defaultChannel,calibration);
    std::vector<ChannelsInfo> infoBscan;
    for(uint8_t i=0; i<calibration.getChannelsCount(); i++) {
        const auto & channel = calibration.getChannel(i);
        const auto & dispChannels = channel.getDisplayChannels();
        for(size_t j=0; j<dispChannels.size(); j++) {
            ChannelsInfo info;
            info._channel = i;
            info._displayChannel = j;
            infoBscan.push_back(info);
        }
    }
    ui->bScanPage->init(calibration);
    ui->bScanPage->setChannles(infoBscan,calibration);
    ui->channelsWidget->init(calibration,tactTableSnapshot);
    _calibrationsWidget->init(calibration);
    _memoryWidget->init();
    _optionsWidget->init();
    _registrationWidget->init();
}

void MainWindow::reset()
{
    Q_ASSERT(_core);
    ui->aScanPage->reset();
    ui->tvgEditorWidget->reset();
    ui->bScanPage->reset();
}
