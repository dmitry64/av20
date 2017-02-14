#ifndef BSCANPAGE_H
#define BSCANPAGE_H

#include <QWidget>

#include "bscanwidget.h"
#include "core.h"

namespace Ui {
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
    void init(DeviceCalibration * snapshot);

    void setChannles(std::vector< std::vector<Channel> > channelsConfiguration);
public slots:
    void onBScan(QSharedPointer<BScanDrawData> scan);
    void onDisplayPackage(QSharedPointer<DisplayPackage> dp);
    void onChannelChanged(Channel channel);
signals:
    void drawBScan(QSharedPointer<BScanDrawData> scan);
private:
    Ui::BScanPage *ui;
};

#endif // BSCANPAGE_H
