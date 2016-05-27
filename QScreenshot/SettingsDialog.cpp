#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

#include <QSettings>

static const QString SETTINGS_ORGANIZATION  = QString("Dawid Bautsch");
static const QString SETTINGS_APPLICATION   = QString("QScreenshot");

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    ReadSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::closeEvent(QCloseEvent *)
{
    ReadSettings();
}

void SettingsDialog::on_pushButton_clicked()
{
    //!<    save button clicked

    WriteSettings();
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

void SettingsDialog::ReadSettings()
{
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    ui->horizontalSlider->setValue(settings.value("JPEG_Quality", 80).toInt());
    ui->horizontalSlider_2->setValue(settings.value("PNG_Quality", 7).toInt());
}

void SettingsDialog::WriteSettings()
{
    QSettings settings(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    settings.setValue("JPEG_Quality", ui->horizontalSlider->value());
    settings.setValue("PNG_Quality", ui->horizontalSlider_2->value());
}

void SettingsDialog::on_horizontalSlider_valueChanged(int value)
{
    on_horizontalSlider_sliderMoved(value);
}

void SettingsDialog::on_horizontalSlider_2_valueChanged(int value)
{
    ui->label_4->setText(QString::number(value));
}