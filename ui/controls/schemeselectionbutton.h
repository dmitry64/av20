#ifndef SCHEMESELECTIONBUTTON_H
#define SCHEMESELECTIONBUTTON_H

#include <QWidget>

namespace Ui
{
class SchemeSelectionButton;
}

class SchemeSelectionButton : public QWidget
{
    Q_OBJECT

    uint8_t _index;
public:
    explicit SchemeSelectionButton(QWidget *parent = 0);
    ~SchemeSelectionButton();
    void setText(const QString &text);
    void setIndex(uint8_t index);
private slots:
    void on_mainButton_released();

signals:
    void schemeSelected(uint8_t index);
private:
    Ui::SchemeSelectionButton *ui;
    void changeEvent(QEvent *event);
};

#endif // SCHEMESELECTIONBUTTON_H
