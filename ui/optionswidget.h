#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>
#include "common/definitions.h"
#include "common/commonfunctions.h"
#include "system/system.h"

namespace Ui
{
class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

private:
    void initOperators(System *system);
public:
    explicit OptionsWidget(QWidget *parent = 0);
    ~OptionsWidget();
    void init();
public slots:
    void onBrightnessChanged(double value);
    void onSoundVolumeChanged(double value);
    void onColorSchemeIndexChanged(size_t index);
signals:
    void colorSchemeChanged(UiTheme);

private slots:
    void on_showFps_toggled(bool checked);
    void on_selectOperatorButton_released();
    void on_removeOperatorButton_released();
    void on_addOperatorButton_released();

    void onOperatorsListChanged();
private:
    Ui::OptionsWidget *ui;
};

#endif // OPTIONSWIDGET_H
