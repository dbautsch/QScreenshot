#include "PictureInfoDialog.h"
#include "ui_PictureInfoDialog.h"

PictureInfoDialog::PictureInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureInfoDialog)
{
    ui->setupUi(this);
}

PictureInfoDialog::~PictureInfoDialog()
{
    delete ui;
}

void PictureInfoDialog::on_toolButton_2_clicked()
{
    //!<    save to file clicked


}

void PictureInfoDialog::on_toolButton_clicked()
{
    //!<    upload to web clicked


}
