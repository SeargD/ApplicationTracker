
#include "applicationtracker.h"
#include "NewApplication/newappdialog.h"
#include "ui_applicationtracker.h"


ApplicationTracker::ApplicationTracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicationTracker)
{
    ui->setupUi(this);
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
