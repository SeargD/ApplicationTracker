#include "newappdialog.h"
#include <QJsonDocument>
#include "ui_newappdialog.h"

NewAppDialog::NewAppDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAppDialog)
{
    ui->setupUi(this);
}

NewAppDialog::~NewAppDialog()
{
    delete ui;
}

void NewAppDialog::WriteToTracker()
{

}

QJsonDocument NewAppDialog::ConstructJson()
{
    return QJsonDocument();
}

void NewAppDialog::on_buttonBox_accepted()
{
    WriteToTracker();
}
