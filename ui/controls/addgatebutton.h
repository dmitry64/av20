#ifndef ADDGATEBUTTON_H
#define ADDGATEBUTTON_H

#include <QWidget>

namespace Ui {
class AddGateButton;
}

class AddGateButton : public QWidget
{
    Q_OBJECT

public:
    explicit AddGateButton(QWidget *parent = 0);
    ~AddGateButton();

private slots:
    void on_addButton_released();
signals:
    void addGate();
private:
    Ui::AddGateButton *ui;
};

#endif // ADDGATEBUTTON_H
