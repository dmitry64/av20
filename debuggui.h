#ifndef DEBUGGUI_H
#define DEBUGGUI_H

#include <QWidget>
#include "core.h"
#include "ui/ascanwidget.h"
#include "ui/controlpanel.h"
#include "device/definitions.h"

namespace Ui {
class DebugGUI;
}

class DebugGUI : public QWidget
{
    Q_OBJECT

    Core * _core;
public:
    explicit DebugGUI(QWidget *parent = 0);
    ~DebugGUI();

    void setCore(Core * core);
    AScanWidget * getAscanWidget();
    ControlPanel * getControlPanel();

private:
    Ui::DebugGUI *ui;

public slots:
    void debug(int value);
    void onConnectionStatusChanged(bool status);
    void onErrorStatusChanged(bool status);
    void onDeviceErrorStatusChanged(bool status);
    void onDeviceOverheatStatusChanged(bool status);
    void onDeviceReadyStatusChanged(bool status);

    void onAScan(AScan scan);
signals:
    void ascan(AScan scan);
private slots:
    void on_exitButton_released();
};

#endif // DEBUGGUI_H
