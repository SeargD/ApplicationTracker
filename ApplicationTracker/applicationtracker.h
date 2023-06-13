
#ifndef APPLICATIONTRACKER_H
#define APPLICATIONTRACKER_H

#include <QTableView>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QFile>
#include <filesystem>
#include <QJsonArray>
#include "currentapplication.h"



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
    void RemoveApplication(QItemSelectionModel* Selected);

    void InitModelView();
    void ParseActionStatus();
    void FitModelToWidth();
    int GetTableWidth();
    QList<QStandardItem*> GetRow(int index);

    bool ConfirmDelete();

    QByteArray BuildDefaultData();

    std::filesystem::path DataFile = std::filesystem::current_path();
    QFile AppDataFile;
    QJsonArray AppData;
    QStandardItemModel AppDataModel;
    CurrentApplication CurrApp;

    QTableView* AppTable;//alias for ui->tApplications

private slots:
    void on_AddApplication_clicked();
    void on_EditApplication_clicked();
    void ApplicationAdded();
    void ApplicationEdited(QList<QStandardItem*> EditRow);
    void EditDiscarded(QList<QStandardItem*> EditRow);
    void on_DeleteApp_clicked();
    void UpdateCurrent();
};

#endif // APPLICATIONTRACKER_H
