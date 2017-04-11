#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "core.h"
#include "ui/helpwidget.h"
#include "ui/modeselectionwidget.h"
#include "ui/calibrationswidget.h"
#include "ui/registrationwidget.h"
#include "ui/memorywidget.h"
#include "ui/optionswidget.h"
#include "ui/systemwidget.h"
#include "system/system.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Core * _core;

    HelpWidget * _helpWidget;
    ModeSelectionWidget * _modeSelectionWidget;
    CalibrationsWidget * _calibrationsWidget;
    RegistrationWidget * _registrationWidget;
    MemoryWidget * _memoryWidget;
    OptionsWidget * _optionsWidget;
    SystemWidget * _systemWidget;
    QPushButton * _backgroundWidget;

    QPalette _defaultPalette;
    QPalette _alternativePalette;

private:
    void closeEvent(QCloseEvent *event);
private slots:
    void setColorScheme(UiTheme theme);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();
    void reset();
    void setCore(Core * core);
public slots:
    void onChannelChanged(Channel channel);
    void onDisplayPackage(QSharedPointer<DisplayPackage> dp);
    void onModeChangeRequested(uint8_t modeIndex, uint8_t tableIndex);
    void onModeChanged();
    void onCalibrationChanged();

    // Menu handlers
    void onHelpMenuOpened();
    void onHelpMenuClosed();
    void onModeMenuOpened();
    void onModeMenuClosed();
    void onCalibrationsMenuOpened();
    void onCalibrationsMenuClosed();
    void onRegistrationMenuOpened();
    void onRegistrationMenuClosed();
    void onMemoryMenuOpened();
    void onMemoryMenuClosed();
    void onOptionsMenuOpened();
    void onOptionsMenuClosed();
    void onSystemMenuOpened();
    void onSystemMenuClosed();

    // Device handlers
    void onDeviceOverheatEnable();
    void onDeviceOverheatDisable();
    void onDeviceErrorEnable();
    void onDeviceErrorDisable();
    void onDeviceConnectionErrorEnable();
    void onDeviceConnectionErrorDisable();

    // System handlers
    void onShutdown();
    void onReboot();
    void onPause();

signals:
    void drawDisplayPackage(QSharedPointer<DisplayPackage> dp);
    void channelChanged(Channel channel);
    void registrationStateChanged(bool);
    void resetMenu();

private:
    Ui::MainWindow *ui;
    void createMenuWidgets();
    void generateUiThemes();
    void createBackgroundWidget();
    void connectMenuWidgets();
    void initBScanPage(const ChannelsCalibration& calibration);
};

#endif // MAINWINDOW_H
