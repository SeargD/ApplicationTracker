#include <QJsonDocument>
#include <QJsonObject>
#include <QErrorMessage>
#include <QMessageBox>
#include <QStandardItemModel>
#include <iostream>
#include "applicationtracker.h"
#include "ApplicationTackerEnums.h"
#include "NewApplication/newappdialog.h"
#include "EditApplication/editappdialog.h"
#include "ui_applicationtracker.h"

ApplicationTracker::ApplicationTracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicationTracker)
{
    ui->setupUi(this);
    AppTable = ui->tApplications;
    DataFile.replace_filename("AppData.json");
    AppDataFile.setFileName(DataFile);
    connect(AppTable, &QTableView::clicked, this, &ApplicationTracker::UpdateCurrent);
    InitModelView();
}

ApplicationTracker::~ApplicationTracker()
{
    delete ui;
}


void ApplicationTracker::on_AddApplication_clicked()
{
    NewAppDialog NewApp(this, &AppData);
    connect(&NewApp, &NewAppDialog::ApplicationAdded, this, &ApplicationTracker::ApplicationAdded, Qt::SingleShotConnection);

    NewApp.exec();
}

void ApplicationTracker::on_EditApplication_clicked()
{
    QItemSelectionModel* Selected = AppTable->selectionModel();
    if(!Selected->hasSelection()) return;
    int RowSelected = Selected->selectedRows()[0].row();
    QList<QStandardItem*> lisToPass = AppDataModel.takeRow(RowSelected);
    if(lisToPass.empty()) return;
    EditAppDialog EditApp(this,lisToPass);
    connect(&EditApp, &EditAppDialog::ApplicationEdited, this, &ApplicationTracker::ApplicationEdited);
    connect(&EditApp, &EditAppDialog::EditDiscarded, this, &ApplicationTracker::EditDiscarded);
    EditApp.exec();
}

void ApplicationTracker::on_DeleteApp_clicked()
{
    QItemSelectionModel* Selected = AppTable->selectionModel();
    if(!Selected->hasSelection()) return;

    if(!ConfirmDelete()) return;

    RemoveApplication(Selected);
}

void ApplicationTracker::UpdateCurrent()
{
    QItemSelectionModel* Selected = AppTable->selectionModel();
    if(!Selected->hasSelection()) return;
    int RowSelected = Selected->selectedRows()[0].row();
    ui->tbSelApplication->setText(CurrApp.UpdateView(GetRow(RowSelected)));
}

void ApplicationTracker::ApplicationAdded()
{
    //Write array to file with new object added
    WriteJSON();
    AddApplicationToModel();
}

void ApplicationTracker::ApplicationEdited(QList<QStandardItem*> EditRow)
{
    //Add List to model
    AppDataModel.appendRow(EditRow);
    //Convert list to JSON
    QJsonObject OutputObject = QJsonObject();
    for (int i = 0; i < EditRow.count(); i++)
    {
        QJsonValue Data = EditRow[i]->data(Qt::DisplayRole).toString();
        OutputObject.insert(QString::number(i), Data);
    }
    QJsonArray::iterator itAppData = AppData.begin();
    while (itAppData != AppData.end())
    {
        //Match edited application to JSON file
        if (itAppData->toObject()["0"] == OutputObject["0"])
        {
            //Replace JSON old object with new object
            for(QString& Key: OutputObject.keys())
            {
                QJsonValueRef Temp(itAppData->toObject()[Key]);
                Temp = OutputObject[Key];
            }
        }

        itAppData++;
    }

    WriteJSON();
    ParseActionStatus();
}

void ApplicationTracker::EditDiscarded(QList<QStandardItem*> EditRow)
{
    AppDataModel.appendRow(EditRow);
    //File Write not necessary as data in model unchanged
}

void ApplicationTracker::ReadAppData()
{
    //Initialises empty JSON file if No data file exists
    if(!AppDataFile.exists())
    {
        AppDataFile.open(QIODevice::ReadWrite);
        AppDataFile.write(BuildDefaultData());
        AppDataFile.close();
    }
    AppDataFile.open(QIODevice::ReadOnly, QFileDevice::ReadUser);
    QJsonDocument DataIn = QJsonDocument::fromJson(AppDataFile.readAll());
    AppDataFile.close();

    ParseAppFile(DataIn);
}

void ApplicationTracker::WriteJSON()
{
    AppDataFile.open(QIODevice::WriteOnly);
    QJsonDocument Output(AppData);
    AppDataFile.write(Output.toJson());
    AppDataFile.close();
}

void ApplicationTracker::RemoveApplication(QItemSelectionModel* Selected)
{

    for(auto& index:  Selected->selectedRows(0))
    {
        QString RemovalId(index.data().toString());

        for(int i = 0; i < AppData.count(); i++)
        {
            if(RemovalId == AppData[i].toObject()["0"].toString())
            {
                //Remove from memory
                AppData.removeAt(i);
                break;
            }
        }
        //Remove from model
        AppDataModel.removeRow(index.row());
    }
    //Write to file
    WriteJSON();
}

void ApplicationTracker::InitModelView()
{
    ReadAppData();
    InitialiseModel();
}

void ApplicationTracker::ParseActionStatus()
{
    using namespace ApplicationTrackerEnums;
    for(int i = 0; i < AppDataModel.rowCount(); i++)
    {
        QStandardItem* ReadItem = AppDataModel.item(i, 8);
        ReadItem->setText(ReadAppStatus(ReadItem->data().toInt()));
    }

    for(int i = 0; i < AppDataModel.rowCount(); i++)
    {
        QStandardItem* ReadItem = AppDataModel.item(i, 11);
        ReadItem->setText(ReadAction(ReadItem->data().toInt()));
    }

    for(int i = 0; i < AppDataModel.rowCount(); i++)
    {
        QStandardItem* ReadItem = AppDataModel.item(i, 12);
        ReadItem->setText(ReadAction(ReadItem->data().toInt()));
    }
}

void ApplicationTracker::InitTableView()
{
    AppTable->setModel(&AppDataModel);
    AppTable->hideColumn(0);
    AppTable->hideColumn(3);
    AppTable->verticalHeader()->hide();
    AppTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    AppTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    AppTable->setSizeIncrement(QSizePolicy::Minimum, QSizePolicy::Minimum);
    AppTable->show();
    FitModelToWidth();
}

void ApplicationTracker::ParseAppFile(QJsonDocument& DataIn)
{
    //Checks if input data is valid JSON array. Displays error message if input file is invalid JSON or not array
    if(!DataIn.isArray())
    {
        QErrorMessage FileInputError(this);
        FileInputError.showMessage("Input file failed to parse. Input is not array.");
        FileInputError.exec();
        emit exit(-1); //Exits application to avoid unintended data loss due to improper file edits
    }

    AppData = DataIn.array();
}

void ApplicationTracker::InitialiseModel()
{
    AppDataModel.setRowCount(AppData.count());
    int NumColumns = 0;

    //Check for 0 length array in JSON file. Abort initialisation to allow application to start successfully
    if(!AppData.count()) return;

    QStringList Keys(AppData[0].toObject().keys());


    for(QString& S: Keys)
    {
        NumColumns++;
    }

    AppDataModel.setColumnCount(NumColumns);

    SetColumnHeaders();

    for (int row = 0; row < AppDataModel.rowCount(); ++row)
    {
        for (int column = 0; column < AppDataModel.columnCount(); ++column)
        {
            QJsonObject TempObject = AppData[row].toObject();
            QJsonValue Data = TempObject[QString::number(column)];
            QStandardItem* item = new QStandardItem(QString(Data.toString()));
            AppDataModel.setItem(row, column, item);
        }
    }

    ParseActionStatus();
}

void ApplicationTracker::SetColumnHeaders()
{
    AppDataModel.setHeaderData(0, Qt::Horizontal, QVariant("id"), Qt::DisplayRole);
    AppDataModel.setHeaderData(1, Qt::Horizontal, QVariant("Date Applied"), Qt::DisplayRole);
    AppDataModel.setHeaderData(2, Qt::Horizontal, QVariant("Job Title"), Qt::DisplayRole);
    AppDataModel.setHeaderData(3, Qt::Horizontal, QVariant("Job Description"), Qt::DisplayRole);
    AppDataModel.setHeaderData(4, Qt::Horizontal, QVariant("Company Name"), Qt::DisplayRole);
    AppDataModel.setHeaderData(5, Qt::Horizontal, QVariant("Advert"), Qt::DisplayRole);
    AppDataModel.setHeaderData(6, Qt::Horizontal, QVariant("Contact"), Qt::DisplayRole);
    AppDataModel.setHeaderData(7, Qt::Horizontal, QVariant("Contact Info"), Qt::DisplayRole);
    AppDataModel.setHeaderData(8, Qt::Horizontal, QVariant("Application Status"), Qt::DisplayRole);
    AppDataModel.setHeaderData(9, Qt::Horizontal, QVariant("Followup Date"), Qt::DisplayRole);
    AppDataModel.setHeaderData(10, Qt::Horizontal, QVariant("Last Update"), Qt::DisplayRole);
    AppDataModel.setHeaderData(11, Qt::Horizontal, QVariant("Last Action"), Qt::DisplayRole);
    AppDataModel.setHeaderData(12, Qt::Horizontal, QVariant("Follow-up Action"), Qt::DisplayRole);
}

void ApplicationTracker::AddApplicationToModel()
{
    //Take last JSON object in array
    QJsonObject TempObject(AppData.last().toObject());

    //Build Map from Object
    QMap<int, QString> mapNewApp;
    for(QString& S: TempObject.keys())
    {
        QString Value(TempObject[S].toString());
        mapNewApp.insert(S.toInt(), Value);
    }

    //Use Map to initialise list of items
    QList<QStandardItem*> lisNewApp;
    for(QString& S: mapNewApp)
    {
        QStandardItem* NewItem = new QStandardItem(S);
        lisNewApp.append(NewItem);
    }
    //Add row to item model using generated list
    AppDataModel.appendRow(lisNewApp);

    FitModelToWidth();
    ParseActionStatus();
}

void ApplicationTracker::FitModelToWidth()
{
    AppTable->resizeColumnsToContents();

    //Set Advert width to 120px max. - Doesn't work
    if(AppTable->columnWidth(5) > 240)
    {
        AppTable->setColumnWidth(5, 240);
    }

    //If Total width of columns > widget, return;
    int TotalWidth = GetTableWidth();

    int ViewWidth = ui->tApplications->geometry().width();

    if (TotalWidth > ViewWidth) return;

    int Diff = ViewWidth - TotalWidth;

    int PerColumn = Diff / (AppDataModel.columnCount() - 2); //-2 due to hidden columns

    for(int i = 0; i < AppDataModel.columnCount(); i++)
    {
        if(AppTable->columnWidth(i) > 0)
        {
            if(i == 5 ) continue;//Skips resizing column 5
            AppTable->setColumnWidth(i, AppTable->columnWidth(i) + PerColumn);
            TotalWidth += PerColumn;
            if(TotalWidth > ViewWidth - PerColumn) return;
        }
    }
}

int ApplicationTracker::GetTableWidth()
{
    int TableWidth = 0;
    for (int i = 0; i < AppDataModel.columnCount(); i++)
    {
        TableWidth += AppTable->columnWidth(i);
    }
    return TableWidth;
}

///Builds list of references to data for display function.
///takeRow() inappropriate due to removing and replacement required in view
QList<QStandardItem*> ApplicationTracker::GetRow(int index)
{
    QList<QStandardItem*> lisToPass;
    for(int i = 0; i < AppDataModel.columnCount(); i++)
    {
        QStandardItem* ItemToPass = AppDataModel.item(index, i);
        lisToPass.append(ItemToPass);
    }
    return lisToPass;
}

bool ApplicationTracker::ConfirmDelete()
{
    QMessageBox DelConf;
    DelConf.setText("Are you sure you wish to delete?");
    DelConf.setInformativeText("Deleting an application is permanent and can not be reversed.");
    DelConf.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    switch(DelConf.exec())
    {
    case (QMessageBox::Yes):
        return true;
    case (QMessageBox::No):
        return false;
    }

    return false;
}

void ApplicationTracker::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    FitModelToWidth();
}

QByteArray ApplicationTracker::BuildDefaultData()
{
    QByteArray Output = "";
    Output += "[]";
    return Output;
}
