#include "PictureInfoDialog.h"
#include "ui_PictureInfoDialog.h"

#include <QFileDialog>
#include <QDateTime>

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
    ui->widget->UnloadImage();

    delete pPixmap;
    pPixmap = NULL;
}

void PictureInfoDialog::on_toolButton_2_clicked()
{
    //!<    save to file clicked

    QString strNamePattern  = "Screen-" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".png";

    QString strFile         = QFileDialog::getSaveFileName(this,
                                                           "Choose destination for file",
                                                           strNamePattern,
                                                           tr("PNG Files (*.png);;JPEG Files (*.jpg);;BMP Files (*.bmp)"));
    if (strFile.isEmpty())
        return;

    emit SavePictureToFile(strFile);
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
    ui->widget->LoadImage(pPixmap);

    ui->label_2->setText(QString::number(pPixmap->width()) + " x " + QString::number(pPixmap->height()));
}
