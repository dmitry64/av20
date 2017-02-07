#ifndef DEBUGGUI_H
#define DEBUGGUI_H

#include <QWidget>
#include "core.h"

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

private:
    Ui::DebugGUI *ui;

public slots:
    void debug(int value);
    void onConnectionStatusChanged(bool status);
    void onErrorStatusChanged(bool status);
};

#endif // DEBUGGUI_H
