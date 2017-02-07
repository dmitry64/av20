#ifndef ASCANWIDGET_H
#define ASCANWIDGET_H

#include <QWidget>
#include "device/definitions.h"

namespace Ui {
class AScanWidget;
}

class AScanWidget : public QWidget
{
    Q_OBJECT

    std::atomic_bool _ready;
    std::vector<QPoint> _points;
public:
    explicit AScanWidget(QWidget *parent = 0);
    ~AScanWidget();
    void paintEvent(QPaintEvent * event);
public slots:
    void onAScan(AScan scan);
private:
    Ui::AScanWidget *ui;
};

#endif // ASCANWIDGET_H
