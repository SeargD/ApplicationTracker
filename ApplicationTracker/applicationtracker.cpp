#include <QJsonDocument>
#include <QErrorMessage>
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
    ReadAppData();
}

ApplicationTracker::~ApplicationTracker()
{
    delete ui;
}


void ApplicationTracker::on_AddApplication_clicked()
{
    NewAppDialog NewApp(this);

    NewApp.exec();
}

void ApplicationTracker::ReadAppData()
{
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

void ApplicationTracker::ParseAppFile(QJsonDocument& DataIn)
{
    if(!DataIn.isArray())
    {
        QErrorMessage FileInputError(this);
        FileInputError.showMessage("Input file failed to parse. Input is not array.");
        FileInputError.exec();
        return;
    }
}

QByteArray ApplicationTracker::BuildDefaultData()
{
    QByteArray Output = "";
    Output += "[]";
    return Output;
}
