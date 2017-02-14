#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "core.h"
#include "ui/helpwidget.h"
#include "ui/modeselectionwidget.h"
#include "ui/registrationwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Core * _core;

    HelpWidget * _helpWidget;
    ModeSelectionWidget * _modeSelectionWidget;
    RegistrationWidget * _registrationWidget;
    QPushButton * _backgroundWidget;

private:
    void init();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCore(Core * core);
    void showEvent( QShowEvent* event );
public slots:
    void onChannelChanged(Channel channel);
    void onDisplayPackage(QSharedPointer<DisplayPackage> dp);
    void onHelpMenuOpened();
    void onHelpMenuClosed();
    void onModeMenuOpened();
    void onModeMenuClosed();
    void onRegistrationMenuOpened();
    void onRegistrationMenuClosed();
    void onMemoryMenuOpened();
    void onMemoryMenuClosed();
    void onOptionsMenuOpened();
    void onOptionsMenuClosed();
    void onSystemMenuOpened();
    void onSystemMenuClosed();
signals:
    void drawDisplayPackage(QSharedPointer<DisplayPackage> dp);
    void channelChanged(Channel channel);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
