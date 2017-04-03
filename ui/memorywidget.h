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

    void showEvent( QShowEvent* event );
public:
    explicit MemoryWidget(QWidget *parent = 0);
    ~MemoryWidget();
    void init();
    void updateList();


private slots:
    void on_removeButton_released();

    void on_refreshButton_released();

private:
    Ui::MemoryWidget *ui;
};

#endif // MEMORYWIDGET_H
