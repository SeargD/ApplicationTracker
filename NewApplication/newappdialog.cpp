#include "ApplicationTackerEnums.h"
#include "newappdialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "ui_newappdialog.h"

NewAppDialog::NewAppDialog(QWidget *parent, QJsonArray* DataIn) :
    QDialog(parent),
    ui(new Ui::NewAppDialog)
{
    ui->setupUi(this);
    AppData = DataIn;

    ui->ApplicationDate->setDate(QDate::currentDate()); //Defaults value for application to current date
}

NewAppDialog::~NewAppDialog()
{
    delete ui;
}

void NewAppDialog::WriteToTracker()
{
    //Insert Data from form into JSON array held in memory
    QJsonObject ObjToInsert(ConstructJson());

    AppData->insert(AppData->end(), ObjToInsert);

    emit ApplicationAdded();
    //Don't write to file in this function.Writing to file & model handled by main tracker.
}

QJsonObject NewAppDialog::ConstructJson()
{
    //Build JSON data from form to add to model
    QHash FormData = BuildAppHash();
    QJsonObject Output = QJsonObject();

    QHash<QString, QVariant>::iterator iFormData(FormData.begin());

    while(iFormData != FormData.end())
    {
        if(iFormData.key() == "7")
        {
            Output.insert(iFormData.key(), iFormData.value().toInt());
            iFormData++;
            continue;
        }

        Output.insert(iFormData.key(), iFormData.value().toString());

        iFormData++;
    }

    return Output;
}

///Constructs a Hash of the form data. Hash Ref "/Docs/AppData(Sample Invalid JSON)
QHash<QString, QVariant> NewAppDialog::BuildAppHash()
{
    QHash<QString, QVariant> FormInput = QHash<QString, QVariant>();
    //id - Generate new UUID for application
    QString AppId(QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces));
    FormInput.insert(QString("0"), QVariant(AppId));

    //DateApplied - Pull from ApplicationDate
    FormInput.insert(QString("1"), QVariant(ui->ApplicationDate->date().toString(Qt::DateFormat::ISODate)));

    //JobTitle - Pull from JobTitle
    FormInput.insert(QString("2"), QVariant(ui->JobTitle->text()));

    //JobDescription - Pull from JobDescription
    FormInput.insert(QString("3"), QVariant(ui->JobDescription->toPlainText()));

    //Advert - Pull from AdvertLink
    FormInput.insert(QString("4"), QVariant(ui->AdvertLink->text()));

    //Contact - Pull from ContactName
    FormInput.insert(QString("5"), QVariant(ui->ContactName->text()));

    //ContactAddress - ContactInfo
    FormInput.insert(QString("6"), QVariant(ui->ContactInfo->text()));

    //AppStatus - Default set to applied
    FormInput.insert(QString("7"), QVariant("0"));

    //FollowUpDate - Set 1 week from today
    QDate FollowUpDate = QDate::currentDate().addDays(7);
    FormInput.insert(QString("8"), QVariant(FollowUpDate.toString(Qt::DateFormat::ISODate)));

    //LastUpdate - set to current date
    FormInput.insert(QString("9"), QVariant(QDate::currentDate().toString(Qt::DateFormat::ISODate)));

    //CompanyName - Pull from CompanyName
    FormInput.insert(QString("10"), QVariant(ui->CompanyName->text()));

    //TODO: Implement Input guards for form.Probably in wrong place.
    //InputGuards(FormInput);

    return FormInput;
}

void NewAppDialog::on_buttonBox_accepted()
{
    WriteToTracker();
}

void NewAppDialog::on_TodayButton_clicked()
{
    ui->ApplicationDate->setDate(QDate::currentDate());
}

