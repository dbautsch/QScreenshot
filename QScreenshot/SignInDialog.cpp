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

SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

void SignInDialog::closeEvent(QCloseEvent *)
{
    ui->useLoginPasswordBox->setVisible(true);

    ui->loginEdit->setEnabled(true);
    ui->passwordEdit->setEnabled(true);
}

void SignInDialog::on_pushButton_clicked()
{
    //!<    save login/password
}

void SignInDialog::ShowUseLoginPasswordBox(bool bShow)
{
    ui->useLoginPasswordBox->setVisible(bShow);

    ui->loginEdit->setEnabled(bShow);
    ui->passwordEdit->setEnabled(bShow);
}
