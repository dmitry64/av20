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
    size_t _current;
    QString _name;
private:
    void next();
    void prev();
    void sync();
public:
    explicit TouchSpinBoxString(QWidget *parent = 0);
    ~TouchSpinBoxString();
    void setValues(const std::vector<QString> & values);
    void setName(const QString & name);
    void setIndex(size_t index);

private slots:
    void on_leftButton_pressed();
    void on_rightButton_pressed();
    void on_leftButton_released();
    void on_rightButton_released();
signals:
    void valueChanged(QString value);
    void indexChanged(size_t index);

private:
    Ui::TouchSpinBoxString *ui;
};

#endif // TOUCHSPINBOXSTRING_H
