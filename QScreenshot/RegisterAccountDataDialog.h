#ifndef REGISTERACCOUNTDATADIALOG_H
#define REGISTERACCOUNTDATADIALOG_H

#include <QDialog>

namespace Ui {
class RegisterAccountDataDialog;
}

class RegisterAccountDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit        RegisterAccountDataDialog(QWidget *parent = 0);

                    ~RegisterAccountDataDialog();

    void            closeEvent(QCloseEvent *);

private:
    Ui::RegisterAccountDataDialog *ui;
};

#endif // REGISTERACCOUNTDATADIALOG_H
