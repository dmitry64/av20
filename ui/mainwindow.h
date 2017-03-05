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

private:

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
    void resetMenu();
private slots:
    void on_centralTabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
