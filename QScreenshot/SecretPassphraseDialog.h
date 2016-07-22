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

#ifndef SECRETPASSPHRASEDIALOG_H
#define SECRETPASSPHRASEDIALOG_H

#include <QDialog>

namespace Ui {
class SecretPassphraseDialog;
}

class SecretPassphraseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit        SecretPassphraseDialog(QWidget *parent = 0);

                    ~SecretPassphraseDialog();

    QString         Password();

    bool            RememberPassword();

private slots:
    void            on_SaveButton_clicked();

private:
    Ui::SecretPassphraseDialog *ui;
};

#endif // SECRETPASSPHRASEDIALOG_H
