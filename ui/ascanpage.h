#ifndef ASCANPAGE_H
#define ASCANPAGE_H

#include <QWidget>
#include "common/definitions.h"
#include "core.h"

namespace Ui
{
class AScanPage;
}

class AScanPage : public QWidget
{
    Q_OBJECT

    Core * _core;
private:
    void showEvent( QShowEvent* event );
    ChannelsInfo _current;
public:
    explicit AScanPage(QWidget *parent = 0);
    ~AScanPage();
    void reset();
    void init(ChannelsInfo info);
    void init(ChannelsInfo info, const ChannelsCalibration &snapshot);
    void setCore(Core * core);
    void switchToSelectedChannel();
public slots:
    void onDisplayPackage(QSharedPointer<DisplayPackage> package);
    void onChannelChanged(Channel channel);
    void setChannel(ChannelsInfo info);
signals:
    void drawDisplayPackage(QSharedPointer<DisplayPackage> package);
private:
    Ui::AScanPage *ui;
    void initBScan(ChannelsInfo info, const Channel& ch, const ChannelsCalibration& snapshot);
};

#endif // ASCANPAGE_H
