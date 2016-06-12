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

PasswordsManagerDialog::PasswordsManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordsManagerDialog)
{
    ui->setupUi(this);
}

PasswordsManagerDialog::~PasswordsManagerDialog()
{
    delete ui;
}

void PasswordsManagerDialog::on_pushButton_2_clicked()
{
    //!<    edit selected login/password pair
}

void PasswordsManagerDialog::on_pushButton_3_clicked()
{
    //!<    delete selected login/password pair
}

void PasswordsManagerDialog::on_pushButton_clicked()
{
    //!<    save results
}

void PasswordsManagerDialog::on_pushButton_4_clicked()
{
    //!<    go to secret passphrase setup dialog
}
