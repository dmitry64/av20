#ifndef ASCANPAGE_H
#define ASCANPAGE_H

#include <QWidget>
#include "device/definitions.h"
#include "core.h"

namespace Ui {
class AScanPage;
}

class AScanPage : public QWidget
{
    Q_OBJECT

    Core * _core;

public:
    explicit AScanPage(QWidget *parent = 0);
    ~AScanPage();
    void init(uint8_t channel);
    void init(uint8_t channel, ChannelsCalibration * snapshot);
    void setCore(Core * core);
    void setAScanChannels(std::vector<Channel> channels);
    void setBScanChannels(std::vector<Channel> channels);
public slots:
    //void onAScan(QSharedPointer<AScanDrawData> scan);
    //void onBScan(QSharedPointer<BScanDrawData> scan);
    void onDisplayPackage(QSharedPointer<DisplayPackage> package);
    //void onTVG(TVG tvg);
    void onChannelChanged(Channel channel);
    void setChannel(uint8_t channel);
signals:
    void drawDisplayPackage(QSharedPointer<DisplayPackage> package);
private:
    Ui::AScanPage *ui;
};

#endif // ASCANPAGE_H
