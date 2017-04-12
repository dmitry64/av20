#ifndef TVGEDITORWIDGET_H
#define TVGEDITORWIDGET_H

#include <QWidget>
#include "common/definitions.h"
#include "device/channelscalibration.h"
#include "core.h"
#include "device/tvg/tvgtwopoints.h"
#include "controls/verticaltouchspinbox.h"
namespace Ui
{
class TVGEditorWidget;
}

class TVGEditorWidget : public QWidget
{
    Q_OBJECT

    Core * _core;
    ChannelsInfo _info;
    int _npointNumber;
    std::vector<VerticalTouchSpinBox*> _npointsControls;
    std::vector<std::pair<double, double> > _npointsValues;
private:
    void showEvent( QShowEvent* event );
    TVGTwoPoints * createTVGTwoPointsFromValues();
    TVGNPoints * createTVGNPointsFromValues();
    void initNPointButtons();
    void updateNPointsTVG();
public:
    explicit TVGEditorWidget(QWidget *parent = 0);
    ~TVGEditorWidget();
    void reset();
    void init(const ChannelsInfo &info);
    void init(const ChannelsInfo &info, const ChannelsCalibration &snapshot);
    void initCurve(const TVGCurve *curve);
    void setCore(Core * core);
    void switchToSelectedChannel();
public slots:
    void onDisplayPackage(QSharedPointer<DisplayPackage> package);
    void onChannelChanged(Channel channel);
    void setChannel(ChannelsInfo info);

    void onSingleOffsetChanged(double value);
    void onSingleHeightChanged(double value);
    void onSingleBaseChanged(double value);
    void onSingleWidthChanged(double value);
    void onSingleFormChanged(double value);

    void onNPointNumberChanged(double value);
    void onNPointValueChanged(double value);

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::TVGEditorWidget *ui;
    void setupTwoPoint();
};

#endif // TVGEDITORWIDGET_H
