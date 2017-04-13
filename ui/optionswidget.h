#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>
#include "common/definitions.h"
#include "common/commonfunctions.h"
#include "system/system.h"
#include "localization/localization.h"

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
    void addOperatorWithName(const QString & name);
    void on_showFps_toggled(bool checked);
    void on_selectOperatorButton_released();
    void on_removeOperatorButton_released();
    void on_addOperatorButton_released();
    void onLanguageChanged(size_t index);

    void onOperatorsListChanged();
private:
    Ui::OptionsWidget *ui;
    void initColorSchemes(const Settings* settings);
    void initLanguages();
    void initBrightness(System* system);
    void initSound(System* system);
    void initDebug(const Settings* settings);
    void changeEvent(QEvent *event);
};

#endif // OPTIONSWIDGET_H
