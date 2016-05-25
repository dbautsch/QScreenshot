#include "PictureInfoDialog.h"
#include "ui_PictureInfoDialog.h"

PictureInfoDialog::PictureInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureInfoDialog)
{
    ui->setupUi(this);

    pPixmap = NULL;
}

PictureInfoDialog::~PictureInfoDialog()
{
    delete ui;
}

void PictureInfoDialog::showEvent(QShowEvent *)
{
    LoadPreview();
}

void PictureInfoDialog::closeEvent(QCloseEvent *)
{
    delete pPixmap;
    pPixmap = NULL;
}

void PictureInfoDialog::on_toolButton_2_clicked()
{
    //!<    save to file clicked


}

void PictureInfoDialog::on_toolButton_clicked()
{
    //!<    upload to web clicked


}

void PictureInfoDialog::SetImage(QPixmap * pPixmap)
{
    this->pPixmap = pPixmap;
}

void PictureInfoDialog::LoadPreview()
{
    ui->label_2->setPixmap(*pPixmap);
}
