#include "englishkeyboard.h"
#include "ui_englishkeyboard.h"

EnglishKeyboard::EnglishKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnglishKeyboard)
{
    ui->setupUi(this);
}

EnglishKeyboard::~EnglishKeyboard()
{
    delete ui;
}

void EnglishKeyboard::on_q_released()
{
    emit textTyped("q");
}

void EnglishKeyboard::on_w_released()
{
    emit textTyped("w");
}

void EnglishKeyboard::on_e_released()
{
    emit textTyped("e");
}

void EnglishKeyboard::on_r_released()
{
    emit textTyped("r");
}

void EnglishKeyboard::on_t_released()
{
    emit textTyped("t");
}

void EnglishKeyboard::on_y_released()
{
    emit textTyped("y");
}

void EnglishKeyboard::on_u_released()
{
    emit textTyped("u");
}

void EnglishKeyboard::on_i_released()
{
    emit textTyped("i");
}

void EnglishKeyboard::on_o_released()
{
    emit textTyped("o");
}

void EnglishKeyboard::on_a_released()
{
    emit textTyped("a");
}

void EnglishKeyboard::on_s_released()
{
    emit textTyped("s");
}

void EnglishKeyboard::on_d_released()
{
    emit textTyped("d");
}

void EnglishKeyboard::on_f_released()
{
    emit textTyped("f");
}

void EnglishKeyboard::on_g_released()
{
    emit textTyped("g");
}

void EnglishKeyboard::on_h_released()
{
    emit textTyped("h");
}

void EnglishKeyboard::on_j_released()
{
    emit textTyped("j");
}

void EnglishKeyboard::on_k_released()
{
    emit textTyped("k");
}

void EnglishKeyboard::on_p_released()
{
    emit textTyped("p");
}

void EnglishKeyboard::on_z_released()
{
    emit textTyped("z");
}

void EnglishKeyboard::on_x_released()
{
    emit textTyped("x");
}

void EnglishKeyboard::on_c_released()
{
    emit textTyped("c");
}

void EnglishKeyboard::on_v_released()
{
    emit textTyped("v");
}

void EnglishKeyboard::on_b_released()
{
    emit textTyped("b");
}

void EnglishKeyboard::on_n_released()
{
    emit textTyped("n");
}

void EnglishKeyboard::on_m_released()
{
    emit textTyped("m");
}

void EnglishKeyboard::on_l_released()
{
    emit textTyped("l");
}
