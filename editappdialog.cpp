#include "editappdialog.h"
#include "ui_editappdialog.h"

EditAppDialog::EditAppDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAppDialog)
{
    ui->setupUi(this);
}

EditAppDialog::~EditAppDialog()
{
    delete ui;
}
