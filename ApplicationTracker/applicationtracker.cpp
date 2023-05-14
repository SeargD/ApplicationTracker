#include <QJsonDocument>
#include <QJsonObject>
#include <QErrorMessage>
#include <QStandardItemModel>
#include <iostream>
#include "applicationtracker.h"
#include "NewApplication/newappdialog.h"
#include "ui_applicationtracker.h"

ApplicationTracker::ApplicationTracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicationTracker)
{
    ui->setupUi(this);
    AppTable = ui->tApplications;
    DataFile.replace_filename("AppData.json");
    AppDataFile.setFileName(DataFile);
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

}

void ApplicationTracker::ApplicationAdded()
{
    //Write array to file with new object added
    AppDataFile.open(QIODevice::WriteOnly);
    QJsonDocument Output(AppData);
    AppDataFile.write(Output.toJson());
    AppDataFile.close();

    AddApplicationToModel();
}

//Call from InitModelView()
void ApplicationTracker::ReadAppData()//Function needs refactor. Does too much.
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

void ApplicationTracker::InitModelView()
{
    ReadAppData();
    InitialiseModel();
}

void ApplicationTracker::InitTableView()
{

    AppTable->setModel(&AppDataModel);
    AppTable->hideColumn(0);
    AppTable->hideColumn(3);
    AppTable->verticalHeader()->hide();
    AppTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    AppTable->setSelectionBehavior(QAbstractItemView::SelectRows);
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
}

void ApplicationTracker::FitModelToWidth()
{
    AppTable->resizeColumnsToContents();

    //Set Advert width to 120px max.
    if(AppTable->columnWidth(5) > 120)
    {
        AppTable->setColumnWidth(5, 120);
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
            AppTable->setColumnWidth(i, AppTable->columnWidth(i) + PerColumn);
            TotalWidth += PerColumn;
        }
    }
}

int ApplicationTracker::GetTableWidth()
{
    int TableWidth = 0;
    for (int i = 0; i < AppDataModel.columnCount(); i++)
    {
        TableWidth += ui->tApplications->columnWidth(i);
    }
    return TableWidth;
}

QByteArray ApplicationTracker::BuildDefaultData()
{
    QByteArray Output = "";
    Output += "[]";
    return Output;
}


