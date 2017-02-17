#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QWidget>

namespace Ui {
class SystemWidget;
}

class SystemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemWidget(QWidget *parent = 0);
    ~SystemWidget();

private slots:
    void on_shutdownButton_released();
    void on_rebootButton_released();
    void on_pauseButton_released();

signals:
    void pause();
    void reboot();
    void shutdown();

private:
    Ui::SystemWidget *ui;
};

#endif // SYSTEMWIDGET_H