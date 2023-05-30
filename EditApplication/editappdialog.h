#ifndef EDITAPPDIALOG_H
#define EDITAPPDIALOG_H

#include <QDialog>
#include <QStandardItem>

namespace Ui {
class EditAppDialog;
}

class EditAppDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAppDialog(QWidget *parent = nullptr, QList<QStandardItem*> lisInput = QList<QStandardItem*>());
    ~EditAppDialog();

private:
    Ui::EditAppDialog *ui;
    QList<QStandardItem*> DataIn;
    QList<QStandardItem*> DataOut;
    void InitialiseFields();
    void InitialiseStatusCombo();
    void InitialiseActionCombo();
    void SetDataOut();

signals:
    void ApplicationEdited(QList<QStandardItem*> DataOut);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // EDITAPPDIALOG_H
