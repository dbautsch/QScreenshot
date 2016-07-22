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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

static const QString SETTINGS_ORGANIZATION  = QString("Dawid Bautsch");
static const QString SETTINGS_APPLICATION   = QString("QScreenshot");

class PasswordsShelter;

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit                SettingsDialog(QWidget *parent = 0);

                            ~SettingsDialog();

    void                    closeEvent(QCloseEvent *);

    void                    ReadSettings();

    void                    WriteSettings();

    void                    SetPasswordsShelter(PasswordsShelter * pPasswordsShelter);

    void                    SetSecretPassphrase(const QByteArray & baPassphraseSHA);

    void                    SetSecretPassphraseSHA(const QByteArray & baPassphraseSHA);

    void                    GetSecretPasspphrase(QByteArray & baPassphraseSHA);

    void                    GetSecretPassphraseSHA(QByteArray & baPassphraseSHA);

private slots:
    void                    on_pushButton_clicked();

    void                    on_horizontalSlider_sliderMoved(int position);

    void                    on_horizontalSlider_2_sliderMoved(int position);

    void                    on_horizontalSlider_valueChanged(int value);

    void                    on_horizontalSlider_2_valueChanged(int value);

    void                    on_pushButton_2_clicked();

public slots:
    void                    SaveApplicationGeometry(const QPoint & ptPos);

signals:
    void                    RestoreApplicationGeometry(const QPoint & ptPos);

private:
    Ui::SettingsDialog  *    ui;

    PasswordsShelter    *    pPasswordsShelter;

    QByteArray              baSecretSHA;        //!< secret passphrase (SHA calculated of the secret pass) used to encrypt passwords in password manager class
                                                //!< will be set only if user has set the option "always remember" in the secret passphrase dialog

    QByteArray              baSecretSHA2;       //!< SHA shortcut calculated from secret passphrase SHA. It is used to check if user has entered correct password in the
                                                //!< passwords manager dialog, it is set when user has set the option "always remember" to false in the secret passphrase dialog.
};

#endif // SETTINGSDIALOG_H
