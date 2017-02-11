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
    AScanWidget * getAscanWidgetSingle();
private:
    Ui::DebugGUI *ui;
    void init();
    void showEvent( QShowEvent* event );

public slots:
    void debug(int value);
    void onConnectionStatusChanged(bool status);
    void onErrorStatusChanged(bool status);
    void onDeviceErrorStatusChanged(bool status);
    void onDeviceOverheatStatusChanged(bool status);
    void onDeviceReadyStatusChanged(bool status);

    void onAScan(QSharedPointer<AScanDrawData> scan);
    void onBScan(QSharedPointer<BScanDrawData> scan);
    void onTVG(TVG tvg);

    void onDisplayPackage(QSharedPointer<DisplayPackage> dp);
    //void onChannelChanged(uint8_t channel);
signals:
    //void AScanSingle(AScan scan);
    void drawDisplayPackage(QSharedPointer<DisplayPackage>);
    void AScanAB(QSharedPointer<AScanDrawData> scan);
    void BScanAB(QSharedPointer<BScanDrawData> scan);
    void TVGReady(TVG tvg);
private slots:
    void on_exitButton_released();
    void on_pushButton_2_released();
    void on_tabWidget_currentChanged(int index);
};

#endif // DEBUGGUI_H
