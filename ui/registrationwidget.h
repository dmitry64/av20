#ifndef REGISTRATIONWIDGET_H
#define REGISTRATIONWIDGET_H

#include <QWidget>

namespace Ui {
class RegistrationWidget;
}

class RegistrationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWidget(QWidget *parent = 0);
    ~RegistrationWidget();

private:
    Ui::RegistrationWidget *ui;
};

#endif // REGISTRATIONWIDGET_H
