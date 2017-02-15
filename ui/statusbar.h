#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = 0);
    ~StatusBar();
    void init();
public slots:
    void onDeviceOverheatEnabled();
    void onDeviceOverheatDisabled();
    void onDeviceErrorEnabled();
    void onDeviceErrorDisabled();
    void onDeviceConnectionErrorEnabled();
    void onDeviceConnectionErrorDisabled();

private:
    Ui::StatusBar *ui;
};

#endif // STATUSBAR_H
