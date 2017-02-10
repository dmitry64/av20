#ifndef CHANNELBUTTON_H
#define CHANNELBUTTON_H

#include <QWidget>

namespace Ui {
class ChannelButton;
}

class ChannelButton : public QWidget
{
    Q_OBJECT

    QString _name;
    uint8_t _channel;
    bool _state;
public:
    explicit ChannelButton(QString name, uint8_t channel, QWidget *parent = 0);
    ~ChannelButton();
    void setActive(bool state);

private slots:
    void on_channelButton_released();

signals:
    void channelSelected(uint8_t);
private:
    Ui::ChannelButton *ui;
};

#endif // CHANNELBUTTON_H
