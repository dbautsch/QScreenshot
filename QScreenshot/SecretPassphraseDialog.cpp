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

#include "SecretPassphraseDialog.h"
#include "ui_SecretPassphraseDialog.h"

#include <QMessageBox>

SecretPassphraseDialog::SecretPassphraseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecretPassphraseDialog)
{
    ui->setupUi(this);
}

SecretPassphraseDialog::~SecretPassphraseDialog()
{
    delete ui;
}

void SecretPassphraseDialog::on_SaveButton_clicked()
{
    //!< Save password button click.

    if (ui->password1Edit->text().isEmpty() ||
        ui->password2Edit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Secret passphrase"), tr("Please fill each password fields."));
        return;
    }

    if (ui->password1Edit->text() != ui->password2Edit->text())
    {
        QMessageBox::warning(this, tr("Secret passphrase"), tr("Entered passwords are not the same. Please correct your password."));
        return;
    }

    close();
}

QString SecretPassphraseDialog::Password()
{
    return ui->password1Edit->text();
}

bool SecretPassphraseDialog::RememberPassword()
{
    return ui->rememberPasswordBox->isChecked();
}
