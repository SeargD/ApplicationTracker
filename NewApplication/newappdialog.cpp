#include "ApplicationTackerEnums.h"
#include "newappdialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "ui_newappdialog.h"

NewAppDialog::NewAppDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAppDialog)
{
    ui->setupUi(this);
    ui->ApplicationDate->setDate(QDate::currentDate()); //Defaults value for application to current date
}

NewAppDialog::~NewAppDialog()
{
    delete ui;
}

void NewAppDialog::WriteToTracker()
{
    //Insert Data from form into JSON array held in memory
    //Don't write to file in this function.(maybe)
}

QJsonObject NewAppDialog::ConstructJson()
{
    //Build JSON data from form to add to model
    BuildAppHash();


    return QJsonObject();
}

///Constructs a Hash of the form data. Hash Ref "/Docs/AppData(Sample Invalid JSON)
QHash<QString, QVariant> NewAppDialog::BuildAppHash()
{
    QHash<QString, QVariant> FormInput = QHash<QString, QVariant>();
    //id - Generate new UUID for application
    QString AppId(QUuid::createUuid().toString());
    FormInput.insert(QString("0"), QVariant(AppId));

    //DateApplied - Pull from ApplicationDate
    FormInput.insert(QString("1"), QVariant(ui->ApplicationDate->date().toString(Qt::DateFormat::ISODate)));

    //JobTitle - Pull from JobTitle
    FormInput.insert(QString("2"), QVariant(ui->JobTitle->text()));

    //JobDescription - Pull from JobDescription
    FormInput.insert(QString("3"), QVariant(ui->JobDescription->toPlainText()));

    //Advert - Pull from AdvertLink
    //Contact - Pull from ContactName
    //ContactAddress - ContactInfo
    //AppStatus - Default set to applied
    //FollowUpDate - Set 1 week from today
    //LastUpdate - set to current date

    return FormInput;
}

void NewAppDialog::on_buttonBox_accepted()
{
    WriteToTracker();
}

void NewAppDialog::on_TodayButton_clicked()
{
    //Set Date Applied to the current date
}

