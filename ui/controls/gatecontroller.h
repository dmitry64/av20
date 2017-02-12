#ifndef GATECONTROLLER_H
#define GATECONTROLLER_H

#include <QWidget>

#include "device/definitions.h"

namespace Ui {
class GateController;
}

class GateController : public QWidget
{
    Q_OBJECT

    Gate _gate;
private:
    void updateGate();
public:
    explicit GateController(QWidget *parent = 0);
    ~GateController();
    void setGate(Gate gate);

private slots:
    void on_gateButton_released();
    void on_deleteButton_released();

    void onStartChanged(double value);
    void onFinishChanged(double value);
    void onLevelChanged(double value);

signals:
    void deleteGate(Gate gate, GateController * controller);
    void gateChanged(Gate gate);

private:
    Ui::GateController *ui;
};

#endif // GATECONTROLLER_H
