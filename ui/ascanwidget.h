#ifndef ASCANWIDGET_H
#define ASCANWIDGET_H

#include <QWidget>

namespace Ui {
class AScanWidget;
}

class AScanWidget : public QWidget
{
    Q_OBJECT

    uint8_t * _ascanSource;
    std::atomic_bool _ready;
public:
    explicit AScanWidget(QWidget *parent = 0);
    ~AScanWidget();
    void paintEvent(QPaintEvent * event);
    void setSource(uint8_t * ptr);

private:
    Ui::AScanWidget *ui;
};

#endif // ASCANWIDGET_H
