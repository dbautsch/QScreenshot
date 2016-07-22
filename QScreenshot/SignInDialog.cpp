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

#include "SignInDialog.h"
#include "ui_SignInDialog.h"
#include "ImageUploaders/ImageUploader.h"

#include <QMessageBox>
#include <QDebug>

SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);

    ShowServiceCombo(false);
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

void SignInDialog::showEvent(QShowEvent *)
{
    if (ui->serviceCombo->isVisible())
        FillServicesCombo();
}

void SignInDialog::closeEvent(QCloseEvent *)
{
    ui->useLoginPasswordBox->setVisible(true);

    ui->loginEdit->setEnabled(true);
    ui->passwordEdit->setEnabled(true);

    ShowServiceCombo(false);

    strService.clear();
}

void SignInDialog::ShowUseLoginPasswordBox(bool bShow)
{
    ui->useLoginPasswordBox->setVisible(bShow);

    ui->loginEdit->setEnabled(!bShow);
    ui->passwordEdit->setEnabled(!bShow);
}

void SignInDialog::ShowServiceCombo(bool bShow)
{
    //!< Show an extra control with the list of available services.
    //!< Used only when user want to add new service data to the list.

    ui->label_4->setVisible(bShow);
    ui->serviceCombo->setVisible(bShow);
}

void SignInDialog::SetServiceLogo(const QString & strResourcePath)
{
    ui->logoWidget->setStyleSheet("QWidget{background-image: url(" + strResourcePath + "); background-repeat:none;}");
}

void SignInDialog::on_saveButton_clicked()
{
    //!<    save login/password

    if (ui->loginEdit->text().trimmed().isEmpty() ||
        ui->passwordEdit->text().trimmed().isEmpty()) {

        QMessageBox::information(this, tr("Save password"), tr("Please fill all requiered fields."));
        return;
    }

    if (ui->serviceCombo->isVisible() && ui->serviceCombo->currentIndex() < 0)
    {
        QMessageBox::information(this, tr("Save password"), tr("Please select web service name."));
        return;
    }

    close();
}

QString SignInDialog::LoginInputBox()
{
    //!< Get the login entered by user.

    return ui->loginEdit->text();
}

QString SignInDialog::PasswordInputBox()
{
    //!< Get the password entered by user.

    return ui->passwordEdit->text();
}

QString SignInDialog::ServiceBox()
{
    //!< Get the service choosen by user.

    return ui->serviceCombo->currentText();
}

bool SignInDialog::UsePasswordsShelter()
{
    return ui->usePasswordsShelterBox->isChecked();
}

void SignInDialog::FillServicesCombo()
{
    ServicesList services = ImageUploader::GetServices();

    ui->serviceCombo->clear();

    foreach (const QString & strService, services)
    {
        ui->serviceCombo->addItem(strService);
    }
}

void SignInDialog::SetLogin(const QString & strLogin)
{
    ui->loginEdit->setText(strLogin);
}

void SignInDialog::SetService(const QString & strService)
{
    this->strService = strService;
}
