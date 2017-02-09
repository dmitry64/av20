#ifndef BSCANWIDGET_H
#define BSCANWIDGET_H

#include <QWidget>
#include "device/definitions.h"

namespace Ui {
class BScanWidget;
}

class BScanWidget : public QWidget
{
    Q_OBJECT

    std::vector<AScan> _scans;
public:
    explicit BScanWidget(QWidget *parent = 0);
    ~BScanWidget();
    void paintEvent(QPaintEvent * event);

public slots:
    void onAScan(AScan scan);
private:
    Ui::BScanWidget *ui;
};

#endif // BSCANWIDGET_H
