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

    TouchSpinBox * _tvgCurve;

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();
    void setCore(Core * ptr);
    void init();

private:
    void showEvent(QShowEvent *event);

signals:


public slots:
    void tvgChanged(double value);

private:
    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
