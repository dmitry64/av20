#ifndef TVGEDITORWIDGET_H
#define TVGEDITORWIDGET_H

#include <QWidget>
#include "common/definitions.h"
#include "device/channelscalibration.h"
#include "core.h"

namespace Ui
{
class TVGEditorWidget;
}

class TVGEditorWidget : public QWidget
{
    Q_OBJECT

    Core * _core;
    ChannelsInfo _info;
private:
    void showEvent( QShowEvent* event );
public:
    explicit TVGEditorWidget(QWidget *parent = 0);
    ~TVGEditorWidget();
    void reset();
    void init(ChannelsInfo info);
    void init(ChannelsInfo info, const ChannelsCalibration &snapshot);
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

private:
    Ui::TVGEditorWidget *ui;
};

#endif // TVGEDITORWIDGET_H
