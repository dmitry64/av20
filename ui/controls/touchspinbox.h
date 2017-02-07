#ifndef TOUCHSPINBOX_H
#define TOUCHSPINBOX_H

#include <QWidget>

namespace Ui {
class TouchSpinBox;
}

class TouchSpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit TouchSpinBox(QWidget *parent = 0);
    ~TouchSpinBox();

private:
    Ui::TouchSpinBox *ui;
};

#endif // TOUCHSPINBOX_H
