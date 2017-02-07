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
    std::vector<QPoint> _tvg;
public:
    explicit AScanWidget(QWidget *parent = 0);
    ~AScanWidget();
    void paintEvent(QPaintEvent * event);
public slots:
    void onAScan(AScan scan);
    void onTVG(TVG tvg);
private:
    Ui::AScanWidget *ui;
};

#endif // ASCANWIDGET_H