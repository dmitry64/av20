#ifndef CHANNELBUTTON_H
#define CHANNELBUTTON_H

#include <QWidget>
#include "device/definitions.h"

namespace Ui
{
class ChannelButton;
}

class ChannelButton : public QWidget
{
    Q_OBJECT

    QString _name;
    ChannelID _channel;
    bool _state;
    uint8_t _colorRed;
    uint8_t _colorGreen;
    uint8_t _colorBlue;

public:
    explicit ChannelButton(QString name, uint8_t channel, QWidget *parent = 0);
    ~ChannelButton();
    void setActive(bool state);
    void setColor(uint8_t red,uint8_t green,uint8_t blue);

private slots:
    void on_channelButton_released();

signals:
    void channelSelected(ChannelID);
private:
    Ui::ChannelButton *ui;
};

#endif // CHANNELBUTTON_H
