#ifndef ASCANINFOWIDGET_H
#define ASCANINFOWIDGET_H

#include <QWidget>
#include <device/channel/channel.h>

namespace Ui
{
class AScanInfoWidget;
}

class AScanInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AScanInfoWidget(QWidget *parent = 0);
    ~AScanInfoWidget();
    void setHValue(int value);
    void setChannel(const Channel & chan, DisplayChannelID dispIndex);

private:
    Ui::AScanInfoWidget *ui;
    void changeEvent(QEvent *event);
};

#endif // ASCANINFOWIDGET_H
