#ifndef TOUCHSPINBOX_H
#define TOUCHSPINBOX_H

#include <QWidget>

namespace Ui {
class TouchSpinBox;
}

class TouchSpinBox : public QWidget
{
    Q_OBJECT

    double _value;
    QString _name;
public:
    explicit TouchSpinBox(QString name, QWidget *parent = 0);
    ~TouchSpinBox();

    void setValue(double value);
private:
    Ui::TouchSpinBox *ui;
signals:
    void valueChanged(double value);

private slots:
    void on_leftButton_pressed();
    void on_rightButton_pressed();
};

#endif // TOUCHSPINBOX_H
