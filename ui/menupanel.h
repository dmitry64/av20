#ifndef MENUPANEL_H
#define MENUPANEL_H

#include <QWidget>

namespace Ui
{
class MenuPanel;
}

class MenuPanel : public QWidget
{
    Q_OBJECT

    enum MenuState {
        DefaultState,
        HelpMenuState,
        ModeMenuState,
        CalibrationsMenuState,
        RegistrationMenuState,
        MemoryMenuState,
        OptionsMenuState,
        SystemMenuState
    };

    MenuState _state;
    QPalette _activePalette;
    QPalette _defaultPalette;

private:
    void closeCurrent();
public:
    explicit MenuPanel(QWidget *parent = 0);
    ~MenuPanel();

public slots:
    void resetMenu();

private slots:
    void on_helpButton_released();
    void on_modeButton_released();
    void on_registrationButton_released();
    void on_memoryButton_released();
    void on_optionsButton_released();
    void on_systemButton_released();
    void on_calibrationButton_released();

signals:
    void helpMenuOpened();
    void helpMenuClosed();
    void modeMenuOpened();
    void modeMenuClosed();
    void calibrationsMenuOpened();
    void calibrationsMenuClosed();
    void registrationMenuOpened();
    void registrationMenuClosed();
    void memoryMenuOpened();
    void memoryMenuClosed();
    void optionsMenuOpened();
    void optionsMenuClosed();
    void systemMenuOpened();
    void systemMenuClosed();
private:
    Ui::MenuPanel *ui;
    void changeEvent(QEvent *event);
};

#endif // MENUPANEL_H
