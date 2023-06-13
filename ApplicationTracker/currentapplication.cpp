#include "currentapplication.h"

CurrentApplication::CurrentApplication()
{

}

QString CurrentApplication::UpdateView(QList<QStandardItem*> DataIn)
{
    QString OutputString("");

    Id = DataIn[0]->text();
    Company = DataIn[4]->text();
    Position = DataIn[2]->text();
    Advert = DataIn[5]->text();
    ContactName = DataIn[6]->text();
    ContactInfo = DataIn[7]->text();
    JobDesc = DataIn[3]->text();

    OutputString = ConstructView();
    return OutputString;
}

QString CurrentApplication::ConstructView()
{
    QString OutString("ID: %1 \n\n"
                      "Company: %2 \n\n"
                      "Position: %3 \n\n"
                      "Advert: %4 \n\n"
                      "Contact Name: %5 \n\n"
                      "Contact Info: %6 \n\n"
                      "Job Description: \n%7");
    OutString = OutString.arg(Id,
                              Company,
                              Position,
                              Advert,
                              ContactName,
                              ContactInfo,
                              JobDesc);
    return OutString;
}
