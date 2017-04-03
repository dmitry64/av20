#ifndef CHANNELBUTTON_H
#define CHANNELBUTTON_H

#include <QWidget>
#include "common/definitions.h"

namespace Ui
{
class ChannelButton;
}

class ChannelButton : public QWidget
{
    Q_OBJECT

    QString _name;
    ChannelsInfo _info;
    bool _state;
    uint8_t _colorRed;
    uint8_t _colorGreen;
    uint8_t _colorBlue;
    QPalette _activePalette;
    QPalette _defaultPalette;

public:
    explicit ChannelButton(const QString & name,const ChannelsInfo & info, QWidget *parent = 0);
    ~ChannelButton();
    void setActive(bool state);
    void setColor(uint8_t red,uint8_t green,uint8_t blue);

    ChannelsInfo info() const;
    void setInfo(const ChannelsInfo &info);

private slots:
    void on_channelButton_released();

signals:
    void channelSelected(ChannelsInfo);
private:
    Ui::ChannelButton *ui;
};

#endif // CHANNELBUTTON_H
