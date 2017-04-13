#ifndef BSCANPAGE_H
#define BSCANPAGE_H

#include <QWidget>

#include "bscanwidget.h"
#include "core.h"

namespace Ui
{
class BScanPage;
}

class BScanPage : public QWidget
{
    Q_OBJECT
    Core * _core;
    std::vector<BScanWidget*> _bScanWidgets;
private:
    std::vector<BScanWidget*> getWidgetsByChannel(uint8_t chan);
public:
    explicit BScanPage(QWidget *parent = 0);
    ~BScanPage();

    void setCore(Core * core);
    void init(const ChannelsCalibration &snapshot);
    void reset();
    void setChannles(const std::vector<ChannelsInfo> & channelsConfiguration, const ChannelsCalibration & snapshot);
public slots:
    void onDisplayPackage(QSharedPointer<DisplayPackage> dp);
    void onChannelChanged(Channel channel);
    void setChannel(ChannelsInfo info);
signals:
    void drawBScan(QSharedPointer<BScanDrawData> scan);
private:
    Ui::BScanPage *ui;
    void changeEvent(QEvent *event);
};

#endif // BSCANPAGE_H
