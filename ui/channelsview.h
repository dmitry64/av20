#ifndef CHANNELSVIEW_H
#define CHANNELSVIEW_H

#include <QWidget>
#include <device/devicecalibration.h>

namespace Ui {
class ChannelsView;
}

class ChannelsView : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelsView(QWidget *parent = 0);
    ~ChannelsView();

    void init(DeviceCalibration * snapshot);
private:
    Ui::ChannelsView *ui;
};

#endif // CHANNELSVIEW_H
