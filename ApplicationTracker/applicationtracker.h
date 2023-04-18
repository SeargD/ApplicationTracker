
#ifndef APPLICATIONTRACKER_H
#define APPLICATIONTRACKER_H

#include "applicationtable.h"
#include <QMainWindow>
#include <QFile>
#include <filesystem>
#include <QJsonArray>



QT_BEGIN_NAMESPACE
namespace Ui { class ApplicationTracker; }
QT_END_NAMESPACE

class ApplicationTracker : public QMainWindow

{
    Q_OBJECT

public:
    ApplicationTracker(QWidget *parent = nullptr);
    ~ApplicationTracker();


private:
    Ui::ApplicationTracker *ui;
    void ReadAppData();
    void ParseAppFile(QJsonDocument& DataIn);
    QByteArray BuildDefaultData();

    std::filesystem::path DataFile = std::filesystem::current_path();
    QFile AppDataFile;
    QJsonArray AppData;

    QSharedPointer<ApplicationTable> modelApplications;

private slots:
    void on_AddApplication_clicked();
    void ApplicationAdded();
};

#endif // APPLICATIONTRACKER_H
