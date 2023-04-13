#ifndef NEWAPPDIALOG_H
#define NEWAPPDIALOG_H

#include <QDialog>

namespace Ui {
class NewAppDialog;
}

class NewAppDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAppDialog(QWidget *parent = nullptr);
    ~NewAppDialog();


private:
    Ui::NewAppDialog *ui;
    void WriteToTracker();
    QJsonDocument ConstructJson();
private slots:
    void on_buttonBox_accepted();
};

#endif // NEWAPPDIALOG_H
