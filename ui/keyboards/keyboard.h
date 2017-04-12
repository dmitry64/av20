#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>

namespace Ui
{
class Keyboard;
}

class Keyboard : public QWidget
{
    Q_OBJECT


    bool _isShiftMode;

public:
    explicit Keyboard(QWidget *parent = 0);
    ~Keyboard();

private slots:
    void on_enterButton_released();

    void on_cancelButton_released();

    void onSymbolsSelected(QString str);

    void on_clearButton_released();

    void on_shiftButton_released();

    void on_backspaceButton_released();

signals:
    void textReady(QString);
    void closed();

private:
    Ui::Keyboard *ui;
};

#endif // KEYBOARD_H
