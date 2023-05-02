
#include "applicationtable.h"
#include <QJsonObject>


ApplicationTable::ApplicationTable(QObject* parent, QJsonArray* AppData)
    : QAbstractTableModel(parent)
{
    if(!AppData)
        return;

    JarrData = *AppData;

    InitialiseTable();
}

QVariant ApplicationTable::headerData(int section, Qt::Orientation orientation, int role) const
{


    return QVariant();
}

int ApplicationTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return JarrData.count();

    return -1;
}

int ApplicationTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return Columns.count();

    return -1;
}

QVariant ApplicationTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return QVariant();
}

void ApplicationTable::InitialiseTable()
{
    setHeaderData(0, Qt::Horizontal, QVariant("id"), Qt::DisplayRole);
    setHeaderData(1, Qt::Horizontal, QVariant("Date Applied"), Qt::DisplayRole);
    setHeaderData(2, Qt::Horizontal, QVariant("Company Name"), Qt::DisplayRole);
    setHeaderData(3, Qt::Horizontal, QVariant("Job Title"), Qt::DisplayRole);
    setHeaderData(4, Qt::Horizontal, QVariant("Job Description"), Qt::DisplayRole);
    setHeaderData(5, Qt::Horizontal, QVariant("Advert"), Qt::DisplayRole);
    setHeaderData(6, Qt::Horizontal, QVariant("Contact"), Qt::DisplayRole);
    setHeaderData(7, Qt::Horizontal, QVariant("Contact Info"), Qt::DisplayRole);
    setHeaderData(8, Qt::Horizontal, QVariant("Application Status"), Qt::DisplayRole);
    setHeaderData(9, Qt::Horizontal, QVariant("Followup Date"), Qt::DisplayRole);
    setHeaderData(10, Qt::Horizontal, QVariant("Last Update"), Qt::DisplayRole);
}



