#ifndef ASCANPAGE_H
#define ASCANPAGE_H

#include <QWidget>
#include "device/definitions.h"
#include "core.h"

namespace Ui
{
class AScanPage;
}

class AScanPage : public QWidget
{
    Q_OBJECT

    Core * _core;

public:
    explicit AScanPage(QWidget *parent = 0);
    ~AScanPage();
    void reset();
    void init(const ChannelID channel);
    void init(const ChannelID channel, const ChannelsCalibration &snapshot);
    void setCore(Core * core);
    void setAScanChannels(const std::vector<Channel*> channels);
    void setBScanChannels(const std::vector<Channel*> channels);
public slots:
    void onDisplayPackage(QSharedPointer<DisplayPackage> package);
    void onChannelChanged(Channel *channel);
    void setChannel(ChannelID channel);
signals:
    void drawDisplayPackage(QSharedPointer<DisplayPackage> package);
private:
    Ui::AScanPage *ui;
};

#endif // ASCANPAGE_H
