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

#ifndef PASSWORDSMANAGERDIALOG_H
#define PASSWORDSMANAGERDIALOG_H

#include <QDialog>

class PasswordsShelter;

class SettingsDialog;

namespace Ui {
class PasswordsManagerDialog;
}

class PasswordsManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit                PasswordsManagerDialog(QWidget *parent = 0);

                            ~PasswordsManagerDialog();

    void                    SetPasswordsShelter(PasswordsShelter * pPasswordsShelter);

    void                    showEvent(QShowEvent *);

    void                    SetSettingsDialog(SettingsDialog * pSettings);

private slots:
    void                    on_pushButton_2_clicked();

    void                    on_pushButton_3_clicked();

    void                    on_pushButton_clicked();

    void                    on_pushButton_4_clicked();

    void                    on_pushButton_5_clicked();

private:
    Ui::PasswordsManagerDialog *ui;

    PasswordsShelter    *   pPasswordsShelter;

    SettingsDialog      *   pSettings;


    void                    RefreshContents();
};

#endif // PASSWORDSMANAGERDIALOG_H
