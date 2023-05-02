#include <QJsonDocument>
#include <QErrorMessage>
#include <QStandardItemModel>
#include "applicationtracker.h"
#include "NewApplication/newappdialog.h"
#include "ui_applicationtracker.h"


ApplicationTracker::ApplicationTracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicationTracker)
{
    ui->setupUi(this);
    DataFile.replace_filename("AppData.json");
    AppDataFile.setFileName(DataFile);
    //Initialise model with data from JSON file
    ReadAppData();
    //Show TableView with data initialised
}

ApplicationTracker::~ApplicationTracker()
{
    delete ui;
}


void ApplicationTracker::on_AddApplication_clicked()
{
    NewAppDialog NewApp(this, &AppData);
    connect(&NewApp, &NewAppDialog::ApplicationAdded, this, &ApplicationTracker::ApplicationAdded);

    NewApp.exec();
}

void ApplicationTracker::ApplicationAdded()
{
    //Write array to file with new object added
    AppDataFile.open(QIODevice::WriteOnly);
    QJsonDocument Output(AppData);
    AppDataFile.write(Output.toJson());
    AppDataFile.close();
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

    QStandardItemModel model(4,4);
    for (int row = 0; row < model.rowCount(); ++row) {
        for (int column = 0; column < model.columnCount(); ++column) {
            QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
            model.setItem(row, column, item);
        }
    }

    ui->tApplications->setModel(&model);
    ui->tApplications->show();

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

QByteArray ApplicationTracker::BuildDefaultData()
{
    QByteArray Output = "";
    Output += "[]";
    return Output;
}
