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

#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

#include <QDialog>

namespace Ui {
class SignInDialog;
}

class SignInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit            SignInDialog(QWidget *parent = 0);

                        ~SignInDialog();

    void                showEvent(QShowEvent *);

    void                closeEvent(QCloseEvent *);

    void                ShowUseLoginPasswordBox(bool bShow);

    void                ShowServiceCombo(bool bShow);

    void                SetServiceLogo(const QString &strResourcePath);

    QString             LoginInputBox();

    QString             PasswordInputBox();

    QString             ServiceBox();

    bool                UsePasswordsShelter();

    void                SetLogin(const QString & strLogin);

private slots:

    void                on_saveButton_clicked();

private:
    Ui::SignInDialog *  ui;

    void                FillServicesCombo();
};

#endif // SIGNINDIALOG_H
