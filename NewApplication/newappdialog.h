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
    QJsonObject ConstructJson();
    QHash<QString, QVariant> BuildAppHash();

private slots:
    void on_buttonBox_accepted();
    void on_TodayButton_clicked();
};

#endif // NEWAPPDIALOG_H
