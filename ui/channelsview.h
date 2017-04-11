#ifndef CHANNELSVIEW_H
#define CHANNELSVIEW_H

#include <QWidget>
#include <device/channelscalibration.h>
#include "core.h"

namespace Ui
{
class ChannelsView;
}

class ChannelsView : public QWidget
{
    Q_OBJECT

    Core * _core;
    QColor _disabledChannelsColor;
public:
    explicit ChannelsView(QWidget *parent = 0);
    ~ChannelsView();

    void init();
    void init(const ChannelsCalibration &calibrationsSnapshot, const TactTable &tactTableSnapshot);
    void setCore(Core * core);
    void showEvent( QShowEvent* event );
private:
    Ui::ChannelsView *ui;
    void fillTactsTable(const std::vector<Tact>& tacts, const ChannelsCalibration& calibrationsSnapshot);
    void initChannelsWidget();
    void initTactWidget();
};

#endif // CHANNELSVIEW_H
