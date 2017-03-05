#ifndef CHANNELSELECTOR_H
#define CHANNELSELECTOR_H

#include <QWidget>
#include "core.h"
#include "ui/controls/channelbutton.h"
#include "device/channelscalibration.h"

namespace Ui
{
class ChannelSelector;
}

class ChannelSelector : public QWidget
{
    Q_OBJECT

    Core * _core;
    std::vector<ChannelButton *> _channelButtons;
    ChannelsInfo _selectedChannel;
public:
    explicit ChannelSelector(QWidget *parent = 0);
    ~ChannelSelector();
    void init(const ChannelsCalibration &snapshot);
    void setCore(Core * core);

    ChannelsInfo selectedChannel() const;
    void setSelectedChannel(const ChannelsInfo &selectedChannel);

public slots:
    void onChannelSelected(ChannelsInfo info);

signals:
    void channelChanged(ChannelsInfo info);
private:
    Ui::ChannelSelector *ui;
};

#endif // CHANNELSELECTOR_H
