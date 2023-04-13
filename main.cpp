
#include "ApplicationTracker/applicationtracker.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationTracker w;
    w.show();
    return a.exec();
}
