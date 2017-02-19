#ifndef CALIBRATIONSWIDGET_H
#define CALIBRATIONSWIDGET_H

#include <QWidget>

namespace Ui {
class CalibrationsWidget;
}

class CalibrationsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalibrationsWidget(QWidget *parent = 0);
    ~CalibrationsWidget();

private:
    Ui::CalibrationsWidget *ui;
};

#endif // CALIBRATIONSWIDGET_H
