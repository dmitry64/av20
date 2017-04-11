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
    size_t _prevGatesCount;
    ChannelID _oldChannel;
    ChannelsInfo _info;

public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();
    void setCore(Core * ptr);
    void setChannel(ChannelsInfo info);
    void init(const Channel & channel);

    void initMerkerPos();
    
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
    void fillGates(const std::vector<Gate>& gates);
    void initPrismTime();
    void initFreqency();
    void initPulseProg();
    void clearGates();
};

#endif // CONTROLPANEL_H
