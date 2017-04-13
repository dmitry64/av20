#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui
{
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = 0);
    ~DeleteDialog();
signals:
    void doDelete();
    void doCancel();

private slots:
    void on_deleteButton_released();

    void on_cancelButton_released();

private:
    Ui::DeleteDialog *ui;
    void changeEvent(QEvent *event);
};

#endif // DELETEDIALOG_H
