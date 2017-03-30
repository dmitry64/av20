#ifndef ENGLISHKEYBOARD_H
#define ENGLISHKEYBOARD_H

#include <QWidget>

namespace Ui
{
class EnglishKeyboard;
}

class EnglishKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit EnglishKeyboard(QWidget *parent = 0);
    ~EnglishKeyboard();

private slots:
    void on_q_released();

    void on_w_released();

    void on_e_released();

    void on_r_released();

    void on_t_released();

    void on_y_released();

    void on_u_released();

    void on_i_released();

    void on_o_released();

    void on_a_released();

    void on_s_released();

    void on_d_released();

    void on_f_released();

    void on_g_released();

    void on_h_released();

    void on_j_released();

    void on_k_released();

    void on_p_released();

    void on_z_released();

    void on_x_released();

    void on_c_released();

    void on_v_released();

    void on_b_released();

    void on_n_released();

    void on_m_released();

    void on_l_released();
signals:
    void textTyped(QString);

private:
    Ui::EnglishKeyboard *ui;
};

#endif // ENGLISHKEYBOARD_H
