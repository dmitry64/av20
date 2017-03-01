#ifndef CHANNELSVIEW_H
#define CHANNELSVIEW_H

#include <QWidget>
#include <device/channelscalibration.h>
#include "core.h"

namespace Ui {
class ChannelsView;
}

class ChannelsView : public QWidget
{
    Q_OBJECT

    Core * _core;
public:
    explicit ChannelsView(QWidget *parent = 0);
    ~ChannelsView();

    void init();
    void init(ChannelsCalibration * calibrationsSnapshot, const TactTable *tactTableSnapshot);
    void setCore(Core * core);
    void showEvent( QShowEvent* event );
private:
    Ui::ChannelsView *ui;
};

#endif // CHANNELSVIEW_H
