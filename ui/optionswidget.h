#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>

namespace Ui
{
class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = 0);
    ~OptionsWidget();
    void init();
public slots:
    void onBrightnessChanged(double value);
    void onSoundVolumeChanged(double value);
signals:
    void colorSchemeChanged(QString scheme);

private:
    Ui::OptionsWidget *ui;
};

#endif // OPTIONSWIDGET_H
