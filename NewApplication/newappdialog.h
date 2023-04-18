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
    ///***Set DataIn to JSON Array of application data***
    explicit NewAppDialog(QWidget *parent = nullptr, QJsonArray* DataIn = nullptr);
    ~NewAppDialog();


private:
    Ui::NewAppDialog *ui;
    void WriteToTracker();
    QJsonObject ConstructJson();
    QHash<QString, QVariant> BuildAppHash();

    QJsonArray* AppData = nullptr;

signals:
    void ApplicationAdded();

private slots:
    void on_buttonBox_accepted();
    void on_TodayButton_clicked();
};

#endif // NEWAPPDIALOG_H
