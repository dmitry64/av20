#ifndef ASCANINFOWIDGET_H
#define ASCANINFOWIDGET_H

#include <QWidget>

namespace Ui {
class AScanInfoWidget;
}

class AScanInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AScanInfoWidget(QWidget *parent = 0);
    ~AScanInfoWidget();

private:
    Ui::AScanInfoWidget *ui;
};

#endif // ASCANINFOWIDGET_H
