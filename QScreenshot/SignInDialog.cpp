#include "SignInDialog.h"
#include "ui_SignInDialog.h"

SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

void SignInDialog::on_pushButton_clicked()
{
    //!<    save login/password
}
