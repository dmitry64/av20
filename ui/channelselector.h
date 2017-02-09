#ifndef CHANNELSELECTOR_H
#define CHANNELSELECTOR_H

#include <QWidget>
#include "core.h"

namespace Ui {
class ChannelSelector;
}

class ChannelSelector : public QWidget
{
    Q_OBJECT

    Core * _core;
public:
    explicit ChannelSelector(QWidget *parent = 0);
    ~ChannelSelector();
    void setCore(Core * core);

public slots:
    void onChannelSelected(uint8_t channel);

private:
    Ui::ChannelSelector *ui;
};

#endif // CHANNELSELECTOR_H
