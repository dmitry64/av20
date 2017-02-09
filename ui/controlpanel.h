#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include "core.h"
#include "ui/controls/touchspinbox.h"


namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

    Core * _core;

    TouchSpinBox * _sensBaseLevel;
    int _currentChannel;

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();
    void setCore(Core * ptr);
    void setMode(uint8_t deviceMode);
    void setChannel(int channel);
    void init();

private:
    void showEvent(QShowEvent *event);

signals:


public slots:
    void sensChanged(double value);

private:
    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
