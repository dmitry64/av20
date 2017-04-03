#ifndef TOUCHSPINBOX_H
#define TOUCHSPINBOX_H

#include <QWidget>
#include <QTimer>

namespace Ui
{
class TouchSpinBox;
}

class TouchSpinBox : public QWidget
{
    Q_OBJECT

    double _prev;
    double _value;
    bool _direction;
    QString _name;
    QTimer _timer;
    double _max;
    double _min;
    double _step;
    QString _suffix;

private:
    void inc();
    void dec();
    void sync();
public:
    explicit TouchSpinBox( QWidget *parent = 0);
    ~TouchSpinBox();

    void setValue(double value);
    void setName(const QString & name);
    void setMax(double max);
    void setMin(double min);
    void setStep(double step);
    void setSuffix(const QString & suf);
    double value() const;

private:
    Ui::TouchSpinBox *ui;
signals:
    void valueChanged(double value);

private slots:
    void onTimer();
    void on_leftButton_pressed();
    void on_rightButton_pressed();
    void on_leftButton_released();
    void on_rightButton_released();
};

#endif // TOUCHSPINBOX_H
