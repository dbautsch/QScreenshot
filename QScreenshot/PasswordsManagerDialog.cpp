/*!
*	Copyright (c) 2016 Dawid Bautsch dawid.bautsch@gmail.com
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
*	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
*	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
*	IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*	THE SOFTWARE.
*/

#include "PasswordsManagerDialog.h"
#include "ui_PasswordsManagerDialog.h"
#include "SecretPassphraseDialog.h"
#include "SignInDialog.h"
#include "PasswordsShelter.h"
#include "SettingsDialog.h"

#include <QMessageBox>
#include <QTableWidgetItem>

PasswordsManagerDialog::PasswordsManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordsManagerDialog)
{
    ui->setupUi(this);

    pPasswordsShelter   = nullptr;
    pSettings           = nullptr;
}

PasswordsManagerDialog::~PasswordsManagerDialog()
{
    delete ui;
}

void PasswordsManagerDialog::showEvent(QShowEvent *)
{
    RefreshContents();
}

void PasswordsManagerDialog::on_pushButton_2_clicked()
{
    //!<    edit selected login/password pair

    if (ui->accountsTable->currentRow() < 0)
        return;

    QString strService    = ui->accountsTable->item(ui->accountsTable->currentRow(), 2)->text();
    QString strLogin      = ui->accountsTable->item(ui->accountsTable->currentRow(), 0)->text();

    SignInDialog sid(this);

    sid.ShowServiceCombo(false);
    sid.SetLogin(strLogin);
    sid.SetService(strService);
    sid.exec();

    QString strLogin    = sid.LoginInputBox();
    QString strService  = sid.ServiceBox();

    if (strLogin.isEmpty() || strPassword.isEmpty() || strService.isEmpty())
        return;

    pPasswordsShelter->SetLoginPasswordForService(strService, strLogin, strPassword);
}

void PasswordsManagerDialog::on_pushButton_3_clicked()
{
    //!<    delete selected login/password pair

    if (ui->accountsTable->currentRow() < 0)
        return;

    if (QMessageBox::question(this, ("Delete item"), tr("Are you sure you want to delete selected service details?"))
            != QMessageBox::Yes)
    {
        //  user has cancelled
        return;
    }

    QTableWidgetItem * pItem    = ui->accountsTable->item(ui->accountsTable->currentRow(), 2);
    QString strService          = pItem->text();

    pPasswordsShelter->DeleteServiceInfo(strService);
    RefreshContents();
}

void PasswordsManagerDialog::on_pushButton_clicked()
{
    //!<    save results

    pPasswordsShelter->SubmitChanges();
}

void PasswordsManagerDialog::on_pushButton_4_clicked()
{
    //!<    go to secret passphrase setup dialog

    SecretPassphraseDialog spd(this);
    spd.setModal(true);
    spd.exec();

    if (spd.Password().isEmpty())
        return;
}

void PasswordsManagerDialog::on_pushButton_5_clicked()
{
    //!<    create new login/password pair for given service name

    SignInDialog sid(this);

    sid.ShowServiceCombo(true);
    sid.exec();

    QString strLogin    = sid.LoginInputBox();
    QString strPassword = sid.PasswordInputBox();
    QString strService  = sid.ServiceBox();

    if (strLogin.isEmpty() || strPassword.isEmpty() || strService.isEmpty())
        return;

    pPasswordsShelter->SetLoginPasswordForService(strService, strLogin, strPassword);
}

void PasswordsManagerDialog::SetPasswordsShelter(PasswordsShelter * pPasswordsShelter)
{
    this->pPasswordsShelter = pPasswordsShelter;
}

void PasswordsManagerDialog::RefreshContents()
{
    ui->accountsTable->clear();
    ui->accountsTable->setRowCount(pPasswordsShelter->GetServicesCount());
    ui->accountsTable->setColumnCount(3);

    for (int i = 0; i < pPasswordsShelter->GetServicesCount(); ++i)
    {
        QString strService, strLogin, strPassword;

        pPasswordsShelter->GetServiceAt(i, strService);
        pPasswordsShelter->GetLoginPasswordForService(strService, strLogin, strPassword);

        QString strPasswordDot;

        for (int i = 0; i < strPassword.length(); ++i)
            strPasswordDot += QString::fromStdWString(L"\x2022");

        ui->accountsTable->setItem(i, 0, new QTableWidgetItem(strService));
        ui->accountsTable->setItem(i, 1, new QTableWidgetItem(strLogin));
        ui->accountsTable->setItem(i, 2, new QTableWidgetItem(strPasswordDot));
    }
}

void PasswordsManagerDialog::SetSettingsDialog(SettingsDialog * pSettings)
{
    this->pSettings = pSettings;
}
