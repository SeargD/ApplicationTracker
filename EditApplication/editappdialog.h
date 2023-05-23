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
    void InitialiseFields();
    void InitialiseStatusCombo();
    void InitialiseActionCombo();
    QString ReadAppStatus(int AppStatus);
    QString ReadAction(int Action);
    //OutputFunction - QList<QStandardItyem*>

signals:
    void ApplicationEdited(QList<QStandardItem*> DataOut);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // EDITAPPDIALOG_H
