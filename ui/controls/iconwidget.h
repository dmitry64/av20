#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QWidget>
#include <QIcon>

namespace Ui
{
class IconWidget;
}

class IconWidget : public QWidget
{
    Q_OBJECT

    QIcon _icon;
    QColor _color;
private:
    void paintEvent(QPaintEvent * event);

public:
    explicit IconWidget(QWidget *parent = 0);
    ~IconWidget();
    void setIcon(const QIcon &icon);
    void setColor(const QColor & color);

private:
    Ui::IconWidget *ui;
};

#endif // ICONWIDGET_H
