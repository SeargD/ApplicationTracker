
#ifndef APPLICATIONTRACKER_H
#define APPLICATIONTRACKER_H

#include "applicationtable.h"
#include <QTableView>
#include <QStandardItemModel>
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

    void InitTableView();

protected:
    virtual void resizeEvent(QResizeEvent* event);

private:
    Ui::ApplicationTracker *ui;
    void ParseAppFile(QJsonDocument& DataIn);
    void InitialiseModel();
    void SetColumnHeaders();
    void AddApplicationToModel();
    void ReadAppData();
    void WriteJSON();

    void InitModelView();
    void ParseActionStatus();
    void FitModelToWidth();
    int GetTableWidth();


    QByteArray BuildDefaultData();

    std::filesystem::path DataFile = std::filesystem::current_path();
    QFile AppDataFile;
    QJsonArray AppData;
    QStandardItemModel AppDataModel;

    QTableView* AppTable;

private slots:
    void on_AddApplication_clicked();
    void on_EditApplication_clicked();
    void ApplicationAdded();
    void ApplicationEdited(QList<QStandardItem*> EditRow);
    void EditDiscarded(QList<QStandardItem*> EditRow);
};

#endif // APPLICATIONTRACKER_H
