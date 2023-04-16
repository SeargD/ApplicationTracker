
#include "applicationtable.h"
#include <QJsonObject>


ApplicationTable::ApplicationTable(QObject* parent, QJsonArray* AppData)
    : QAbstractTableModel(parent)
{
    if(!AppData)
        return;

    JarrData = *AppData;
    QStringList Columns = JarrData[0].toObject().keys();


}

QVariant ApplicationTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(!JarrData[0].isObject())
        return QVariant();

    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return Columns[section];

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



