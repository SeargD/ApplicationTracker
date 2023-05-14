#ifndef EDITAPPDIALOG_H
#define EDITAPPDIALOG_H

#include <QDialog>

namespace Ui {
class EditAppDialog;
}

class EditAppDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAppDialog(QWidget *parent = nullptr);
    ~EditAppDialog();

private:
    Ui::EditAppDialog *ui;
};

#endif // EDITAPPDIALOG_H
