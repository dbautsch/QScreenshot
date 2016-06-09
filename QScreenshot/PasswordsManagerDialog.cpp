#include "PasswordsManagerDialog.h"
#include "ui_PasswordsManagerDialog.h"

PasswordsManagerDialog::PasswordsManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordsManagerDialog)
{
    ui->setupUi(this);
}

PasswordsManagerDialog::~PasswordsManagerDialog()
{
    delete ui;
}
