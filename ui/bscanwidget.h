#ifndef BSCANWIDGET_H
#define BSCANWIDGET_H

#include <QWidget>

namespace Ui {
class BScanWidget;
}

class BScanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BScanWidget(QWidget *parent = 0);
    ~BScanWidget();
    void paintEvent(QPaintEvent * event);
private:
    Ui::BScanWidget *ui;
};

#endif // BSCANWIDGET_H
