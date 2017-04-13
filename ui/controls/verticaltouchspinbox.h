#ifndef VERTICALTOUCHSPINBOX_H
#define VERTICALTOUCHSPINBOX_H

#include <QWidget>
#include <QTimer>

namespace Ui
{
class VerticalTouchSpinBox;
}

class VerticalTouchSpinBox : public QWidget
{
    Q_OBJECT

    double _prev;
    double _value;
    bool _direction;
    QString _name;
    int _index;
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
    explicit VerticalTouchSpinBox(QWidget *parent = 0);
    ~VerticalTouchSpinBox();

    void setValue(double value);
    void setName(const QString & name);
    void setMax(double max);
    void setMin(double min);
    void setStep(double step);
    void setSuffix(const QString & suf);
    double value() const;

    int index() const;
    void setIndex(int index);

signals:
    void valueChanged(double value);
private slots:
    void onTimer();
    void on_upButton_pressed();
    void on_upButton_released();
    void on_downButton_pressed();
    void on_downButton_released();

private:
    Ui::VerticalTouchSpinBox *ui;
    void changeEvent(QEvent *event);
};

#endif // VERTICALTOUCHSPINBOX_H
