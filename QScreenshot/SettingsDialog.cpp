#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_pushButton_clicked()
{
    //!<    save button clicked


}

void SettingsDialog::on_horizontalSlider_sliderMoved(int position)
{
    //!<    JPEG compression quality slider has changed

    ui->label_2->setText(QString::number(position));
}

void SettingsDialog::on_horizontalSlider_2_sliderMoved(int position)
{
    //!<    PNG compression quality slider has changed

    ui->label_4->setText(QString::number(position));
}
