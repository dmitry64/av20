#ifndef REGISTRATIONWIDGET_H
#define REGISTRATIONWIDGET_H

#include <QWidget>
#include "core.h"

namespace Ui
{
class RegistrationWidget;
}

class RegistrationWidget : public QWidget
{
    Q_OBJECT

    Core * _core;
    bool _registrationEnabled;
public:
    explicit RegistrationWidget(QWidget *parent = 0);
    void setCore(Core * core);
    void init();
    ~RegistrationWidget();

private slots:
    void on_startButton_released();

private:
    Ui::RegistrationWidget *ui;
};

#endif // REGISTRATIONWIDGET_H
