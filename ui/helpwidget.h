#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>

namespace Ui
{
class HelpWidget;
}

class HelpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HelpWidget(QWidget *parent = 0);
    ~HelpWidget();
    void updateFiles();

private slots:
    void on_listWidget_itemSelectionChanged();

private:
    Ui::HelpWidget *ui;
    void changeEvent(QEvent *event);
};

#endif // HELPWIDGET_H
