#ifndef PASSWORDSMANAGERDIALOG_H
#define PASSWORDSMANAGERDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordsManagerDialog;
}

class PasswordsManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordsManagerDialog(QWidget *parent = 0);
    ~PasswordsManagerDialog();

private:
    Ui::PasswordsManagerDialog *ui;
};

#endif // PASSWORDSMANAGERDIALOG_H
