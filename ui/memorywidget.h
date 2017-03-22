#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>

namespace Ui
{
class MemoryWidget;
}

class MemoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget(QWidget *parent = 0);
    ~MemoryWidget();
    void update();

private:
    Ui::MemoryWidget *ui;
};

#endif // MEMORYWIDGET_H
