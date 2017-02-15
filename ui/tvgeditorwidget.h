#ifndef TVGEDITORWIDGET_H
#define TVGEDITORWIDGET_H

#include <QWidget>
#include "device/definitions.h"
#include "device/devicemode.h"
#include "core.h"

namespace Ui {
class TVGEditorWidget;
}

class TVGEditorWidget : public QWidget
{
    Q_OBJECT

    Core * _core;
public:
    explicit TVGEditorWidget(QWidget *parent = 0);
    ~TVGEditorWidget();
    void init(uint8_t channel);
    void init(uint8_t channel, DeviceMode * snapshot);
    void setCore(Core * core);
public slots:
    void onDisplayPackage(QSharedPointer<DisplayPackage> package);
    void onChannelChanged(Channel channel);
    void setChannel(uint8_t channel);
private:
    Ui::TVGEditorWidget *ui;
};

#endif // TVGEDITORWIDGET_H
