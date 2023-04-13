
#ifndef APPLICATIONTRACKER_H
#define APPLICATIONTRACKER_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class ApplicationTracker; }
QT_END_NAMESPACE

class ApplicationTracker : public QMainWindow

{
    Q_OBJECT

public:
    ApplicationTracker(QWidget *parent = nullptr);
    ~ApplicationTracker();

private slots:
    void on_AddApplication_clicked();

private:
    Ui::ApplicationTracker *ui;
};

#endif // APPLICATIONTRACKER_H
