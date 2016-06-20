#include "RegisterAccountDataDialog.h"
#include "ui_RegisterAccountDataDialog.h"

RegisterAccountDataDialog::RegisterAccountDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterAccountDataDialog)
{
    ui->setupUi(this);
}

RegisterAccountDataDialog::~RegisterAccountDataDialog()
{
    delete ui;
}

void RegisterAccountDataDialog::closeEvent(QCloseEvent *)
{

}
