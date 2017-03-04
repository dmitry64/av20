#ifndef MODESELECTIONBUTTON_H
#define MODESELECTIONBUTTON_H

#include <QWidget>

#include "device/devicemode.h"
#include "ui/controls/schemeselectionbutton.h"

namespace Ui
{
class ModeSelectionButton;
}

class ModeSelectionButton : public QWidget
{
    Q_OBJECT

    DeviceMode _mode;
    uint8_t _index;
public:
    explicit ModeSelectionButton(QWidget *parent = 0);
    ~ModeSelectionButton();
    void setMode(DeviceMode mode, uint8_t index);
public slots:
    void onSchemeSelected(uint8_t index);
signals:
    void modeSelected(uint8_t mode, uint8_t scheme);
private:
    Ui::ModeSelectionButton *ui;
};

#endif // MODESELECTIONBUTTON_H
