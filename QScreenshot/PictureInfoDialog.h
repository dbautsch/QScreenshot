#ifndef PICTUREINFODIALOG_H
#define PICTUREINFODIALOG_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class PictureInfoDialog;
}

class PictureInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit    PictureInfoDialog(QWidget *parent = 0);

                ~PictureInfoDialog();

    void        SetImage(QPixmap * pPixmap);

    void        showEvent(QShowEvent *);

private slots:
    void        on_toolButton_2_clicked();

    void        on_toolButton_clicked();

private:
    Ui::PictureInfoDialog *ui;

    QPixmap *   pPixmap;


    void        LoadPreview();
};

#endif // PICTUREINFODIALOG_H
