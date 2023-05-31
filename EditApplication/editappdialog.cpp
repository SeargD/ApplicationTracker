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
    ui->ApplicationStatus->setCurrentText(ApplicationTrackerEnums::ReadAppStatus(DataIn[8]->data().toInt()));
    ui->FollowUpDate->setDate(QDate::fromString(DataIn[9]->text(), Qt::DateFormat::ISODate));
    ui->LastAction->setText(ApplicationTrackerEnums::ReadAction(DataIn[11]->data().toInt()));
}

void EditAppDialog::InitialiseStatusCombo()
{
    //Code is simple and works but will not reflect additional options if added
    //Making Combo dynamically scale for additional options would likely be over-engineering solution
    for(int i = 0; i <= 5; i++)
    {
        ui->ApplicationStatus->insertItem(i, ApplicationTrackerEnums::ReadAppStatus(i), i);
    }
}

void EditAppDialog::InitialiseActionCombo()
{
    for(int i = 0; i <= 4; i++)
    {
        ui->FollowUpAction->insertItem(i, ApplicationTrackerEnums::ReadAction(i), i);
    }
}

void EditAppDialog::SetDataOut()
{
    //Static variables don't need to be pulled from ui as can not be updated in form
    DataOut.append(DataIn[0]);//Copy id from DataIn
    DataOut.append(DataIn[1]);//Copy DateApplied
    DataOut.append(DataIn[2]);//Copy JobTitle
    DataOut.append(DataIn[3]);//Copy JobDescription
    DataOut.append(DataIn[4]);//Copy CompanyName
    DataOut.append(DataIn[5]);//Copy Advert
    QStandardItem* ContactName = new QStandardItem(ui->ContactName->text());
    DataOut.append(ContactName);
    QStandardItem* ContactInfo = new QStandardItem(ui->ContactInfo->text());
    DataOut.append(ContactInfo);
    QStandardItem* ApplicationStatus = new QStandardItem(QString::number(ui->ApplicationStatus->currentIndex()));
    DataOut.append(ApplicationStatus);
    QStandardItem* FollowUpDate = new QStandardItem(ui->FollowUpDate->date().toString(Qt::ISODate));
    DataOut.append(FollowUpDate);
    QStandardItem* LastUpdate = new QStandardItem(QDate::currentDate().toString(Qt::ISODate));
    DataOut.append(LastUpdate);
    DataOut.append(DataIn[11]);//Copy old FollowUp to become LastAction
    QStandardItem* FollowUpAction = new QStandardItem(QString::number(ui->FollowUpAction->currentIndex()));
    DataOut.append(FollowUpAction);
}

void EditAppDialog::on_buttonBox_accepted()
{
    //Construct output pointer list to return to model
    SetDataOut();
    //Signal output with list
    emit ApplicationEdited(DataOut);
}


void EditAppDialog::on_buttonBox_rejected()
{
    emit EditDiscarded(DataIn);
}

