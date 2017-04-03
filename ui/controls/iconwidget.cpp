#include "iconwidget.h"
#include "ui_iconwidget.h"
#include <QPainter>
#include <QBitmap>

void IconWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(QBrush(_color));
    painter.setPen(QPen(_color));

    painter.fillRect(3,3,width() - 6, height() - 6,_color);
    _icon.paint(&painter,3,3,width()-6,height()-6);

}

IconWidget::IconWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IconWidget)
{
    ui->setupUi(this);

}

IconWidget::~IconWidget()
{
    delete ui;
}

void IconWidget::setIcon(const QIcon &icon)
{
    _icon = icon;
    update();
}

void IconWidget::setColor(const QColor &color)
{
    _color = color;
    update();
}
