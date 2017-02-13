#ifndef MODESELECTIONWIDGET_H
#define MODESELECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class ModeSelectionWidget;
}

class ModeSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModeSelectionWidget(QWidget *parent = 0);
    ~ModeSelectionWidget();

private:
    Ui::ModeSelectionWidget *ui;
};

#endif // MODESELECTIONWIDGET_H
