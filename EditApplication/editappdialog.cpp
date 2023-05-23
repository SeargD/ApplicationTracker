#include <iostream>
#include "editappdialog.h"
#include "ApplicationTackerEnums.h"
#include "ui_editappdialog.h"

EditAppDialog::EditAppDialog(QWidget *parent, QList<QStandardItem*> lisInput) :
    QDialog(parent),
    ui(new Ui::EditAppDialog)
{
    ui->setupUi(this);
    DataIn = lisInput;
    InitialiseFields();
    InitialiseActionCombo();
    InitialiseStatusCombo();
}

EditAppDialog::~EditAppDialog()
{
    delete ui;
}

void EditAppDialog::InitialiseFields()
{
    ui->DateApplied->setText(DataIn[1]->text());
    ui->JobTitle->setText(DataIn[2]->text());
    ui->CompanyName->setText(DataIn[4]->text());
    ui->AdvertLink->setText(DataIn[5]->text());
    ui->ContactName->setText(DataIn[6]->text());
    ui->ContactInfo->setText(DataIn[7]->text());
    ui->ApplicationStatus->setCurrentText(ReadAppStatus(DataIn[8]->text().toInt()));
    ui->FollowUpDate->setDate(QDate::fromString(DataIn[9]->text(), Qt::DateFormat::ISODate));
    ui->LastAction->setText(ReadAction(DataIn[11]->text().toInt()));
}

void EditAppDialog::InitialiseStatusCombo()
{
    //Code is simple and works but will not reflect additional options if added
    //Making Combo dynamically scale for additional options would likely be over-engineering solution
    for(int i = 0; i <= 5; i++)
    {
        ui->ApplicationStatus->insertItem(i, ReadAppStatus(i), i);
    }
}

void EditAppDialog::InitialiseActionCombo()
{
    for(int i = 0; i <= 4; i++)
    {
        ui->FollowUpAction->insertItem(i, ReadAction(i), i);
    }
}

using namespace ApplicationTrackerEnums;
QString EditAppDialog::ReadAppStatus(int AppStatus)
{
    switch(AppStatus)
    {
    case ApplicationStatus::Applied:
        return QString("Applied");
    case ApplicationStatus::NoResponse:
        return QString("No Response");
    case ApplicationStatus::Rejected:
        return QString("Rejected");
    case ApplicationStatus::FollowedUp:
        return QString("Followed Up");
    case ApplicationStatus::Interview:
        return QString("Interview");
    case ApplicationStatus::Offer:
        return QString("Offer");
    default:
        return "";
    }
}

QString EditAppDialog::ReadAction(int Action)
{
    switch(Action)
    {
    case Actions::EmailRecruiter:
        return QString("Email Recruiter");
    case Actions::ArrangeInterview:
        return QString("Arrange Interview");
    case Actions::AttendInterview:
        return QString("Attend Interview");
    case Actions::Wait:
        return QString("Wait");
    case Actions::ObtainFeedback:
        return QString("Obtain Feedback");
    default:
        return "";
    }
}

void EditAppDialog::on_buttonBox_accepted()
{
    //Construct output pointer list to return to model
    //Signal output with list
    //Add List to model (MainWindow)
    //Output edited model to file
}


void EditAppDialog::on_buttonBox_rejected()
{
    //Signal return DataIn to MainWindow with no edits
    //Add DataIn back to model
    //Unnecessary to change file
}

