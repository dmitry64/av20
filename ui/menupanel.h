#ifndef MENUPANEL_H
#define MENUPANEL_H

#include <QWidget>

namespace Ui {
class MenuPanel;
}

class MenuPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPanel(QWidget *parent = 0);
    ~MenuPanel();

private:
    Ui::MenuPanel *ui;
};

#endif // MENUPANEL_H
