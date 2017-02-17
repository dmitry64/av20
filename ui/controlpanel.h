#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include "core.h"
#include "ui/controls/touchspinbox.h"
#include "ui/controls/touchspinboxstring.h"
#include "ui/controls/gatecontroller.h"
#include "ui/controls/addgatebutton.h"

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

    Core * _core;

    TouchSpinBox * _prismTimeSpinbox;
    //TouchSpinBoxString * _frequencySpinbox;
    //TouchSpinBoxString * _progSpinbox;
    TouchSpinBox * _markerPositionSpinbox;
    std::vector<GateController*> _gates;
    QVBoxLayout * _gatesLayout;
    AddGateButton * _addGateButton;
    uint8_t _gateCounter;
    uint8_t _currentChannel;

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();
    void setCore(Core * ptr);
    void setChannel(uint8_t channel);
    void init(ChannelsCalibration *calibration);

private:
    void showEvent(QShowEvent *event);

signals:


public slots:
    void onGateChanged(Gate gate);
    void onDeleteGate(Gate gate, GateController * controller);
    void onAddGate();

private:
    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
