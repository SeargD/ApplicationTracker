#ifndef CURRENTAPPLICATION_H
#define CURRENTAPPLICATION_H

#include <QStandardItem>
#include <QObject>

class CurrentApplication
{
public:
    CurrentApplication();
    QString UpdateView(QList<QStandardItem*> DataIn);

private:
    QString Id;
    QString Company;
    QString Position;
    QString Advert;
    QString ContactName;
    QString ContactInfo;
    QString JobDesc;

    QString ConstructView();
};

#endif // CURRENTAPPLICATION_H
