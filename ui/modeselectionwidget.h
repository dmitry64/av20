#ifndef MODESELECTIONWIDGET_H
#define MODESELECTIONWIDGET_H

#include <QWidget>

#include "core.h"

#include "ui/controls/modeselectionbutton.h"

namespace Ui {
class ModeSelectionWidget;
}

class ModeSelectionWidget : public QWidget
{
    Q_OBJECT

    Core * _core;
    std::vector<ModeSelectionButton*> _buttons;
public:
    explicit ModeSelectionWidget(QWidget *parent = 0);
    ~ModeSelectionWidget();
    void setCore(Core * core);
    void init();
public slots:
    void onModeSelected(uint8_t mode, uint8_t scheme);
signals:
    void modeSelected(uint8_t mode, uint8_t scheme);
    void closeWindow();
private:
    Ui::ModeSelectionWidget *ui;
};

#endif // MODESELECTIONWIDGET_H
