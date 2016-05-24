#ifndef PICTUREINFODIALOG_H
#define PICTUREINFODIALOG_H

#include <QDialog>

namespace Ui {
class PictureInfoDialog;
}

class PictureInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PictureInfoDialog(QWidget *parent = 0);
    ~PictureInfoDialog();

private slots:
    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    Ui::PictureInfoDialog *ui;
};

#endif // PICTUREINFODIALOG_H
