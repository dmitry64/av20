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

    size_t _colorSchemeIndex;
public:
    explicit OptionsWidget(QWidget *parent = 0);
    ~OptionsWidget();
    void init();
public slots:
    void onBrightnessChanged(double value);
    void onSoundVolumeChanged(double value);
    void onColorSchemeChanged(QString str);
signals:
    void colorSchemeChanged(QString scheme);

private:
    Ui::OptionsWidget *ui;
};

#endif // OPTIONSWIDGET_H
