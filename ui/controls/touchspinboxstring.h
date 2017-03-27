#ifndef TOUCHSPINBOXSTRING_H
#define TOUCHSPINBOXSTRING_H

#include <QWidget>

namespace Ui
{
class TouchSpinBoxString;
}

class TouchSpinBoxString : public QWidget
{
    Q_OBJECT

    std::vector<QString> _values;
    unsigned int _current;
    QString _name;
private:
    void next();
    void prev();
    void updateValue();
public:
    explicit TouchSpinBoxString(QWidget *parent = 0);
    ~TouchSpinBoxString();
    void setValues(std::vector<QString> values);
    void setName(QString name);

private slots:
    void on_leftButton_pressed();

    void on_rightButton_pressed();

    void on_leftButton_released();

    void on_rightButton_released();
signals:
    void valueChanged(QString value);

private:
    Ui::TouchSpinBoxString *ui;
};

#endif // TOUCHSPINBOXSTRING_H
