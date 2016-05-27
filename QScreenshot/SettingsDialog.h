#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit                SettingsDialog(QWidget *parent = 0);

                            ~SettingsDialog();

    void                    closeEvent(QCloseEvent *);

private slots:
    void                    on_pushButton_clicked();

    void                    on_horizontalSlider_sliderMoved(int position);

    void                    on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::SettingsDialog *    ui;


    void                    ReadSettings();

    void                    WriteSettings();
};

#endif // SETTINGSDIALOG_H
