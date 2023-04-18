
#ifndef APPLICATIONTABLE_H
#define APPLICATIONTABLE_H

#include <QAbstractTableModel>
#include <QJsonArray>



class ApplicationTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ApplicationTable(QObject *parent = nullptr, QJsonArray* AppData = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QJsonArray JarrData;
    QStringList Columns;

    void InitialiseTable();
};

#endif // APPLICATIONTABLE_H
