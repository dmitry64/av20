#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include "core.h"
#include "ui/controls/touchspinbox.h"
#include "ui/controls/touchspinboxstring.h"
#include "ui/controls/gatecontroller.h"
#include "ui/controls/addgatebutton.h"
#include "common/definitions.h"

namespace Ui
{
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

    Core * _core;

    TouchSpinBox * _prismTimeSpinbox;
    TouchSpinBoxString * _frequencySpinbox;
    TouchSpinBoxString * _progSpinbox;
    TouchSpinBox * _markerPositionSpinbox;
    std::vector<GateController*> _gates;
    QVBoxLayout * _gatesLayout;
    AddGateButton * _addGateButton;
    // uint8_t _gateCounter;
    ChannelsInfo _info;

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();
    void setCore(Core * ptr);
    void setChannel(ChannelsInfo info);
    void init(const Channel & channel);

private:
    void showEvent(QShowEvent *event);

signals:


public slots:
    void onGateChanged(Gate gate);
    void onDeleteGate(Gate gate, GateController * controller);
    void onAddGate();
    void onPrismTimeChanged(double value);

private:
    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
