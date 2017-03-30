#ifndef NUMBERKEYPAD_H
#define NUMBERKEYPAD_H

#include <QWidget>

namespace Ui
{
class NumberKeypad;
}

class NumberKeypad : public QWidget
{
    Q_OBJECT

public:
    explicit NumberKeypad(QWidget *parent = 0);
    ~NumberKeypad();

private slots:
    void on_button1_released();
    void on_button2_released();
    void on_button3_released();
    void on_button4_released();
    void on_button5_released();
    void on_button6_released();
    void on_button7_released();
    void on_button8_released();
    void on_button9_released();
    void on_button0_released();
    void on_sq1_released();
    void on_fig1_released();
    void on_mark_released();
    void on_at_released();
    void on_diez_released();
    void on_percent_released();
    void on_upper_released();
    void on_andButton_released();
    void on_mult_released();
    void on_par1_released();
    void on_par2_released();
    void on_plus_released();
    void on_sq2_released();
    void on_fig2_released();
signals:
    void textTyped(QString);

private:
    Ui::NumberKeypad *ui;
};

#endif // NUMBERKEYPAD_H
