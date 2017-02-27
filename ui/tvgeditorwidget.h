#ifndef TVGEDITORWIDGET_H
#define TVGEDITORWIDGET_H

#include <QWidget>
#include "device/definitions.h"
#include "device/channelscalibration.h"
#include "core.h"

namespace Ui {
class TVGEditorWidget;
}

class TVGEditorWidget : public QWidget
{
    Q_OBJECT

    Core * _core;
    uint8_t _currentChannel;
public:
    explicit TVGEditorWidget(QWidget *parent = 0);
    ~TVGEditorWidget();
    void reset();
    void init(uint8_t channel);
    void init(uint8_t channel, ChannelsCalibration * snapshot);
    void initCurve(TVGCurve * curve);
    void setCore(Core * core);
public slots:
    void onDisplayPackage(QSharedPointer<DisplayPackage> package);
    void onChannelChanged(Channel *channel);
    void setChannel(uint8_t channel);

    void onSingleOffsetChanged(double value);
    void onSingleHeightChanged(double value);
    void onSingleBaseChanged(double value);
    void onSingleWidthChanged(double value);
    void onSingleFormChanged(double value);


private:
    Ui::TVGEditorWidget *ui;
};

#endif // TVGEDITORWIDGET_H
