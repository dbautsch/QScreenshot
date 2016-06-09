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

#ifndef PICTUREINFODIALOG_H
#define PICTUREINFODIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QMenu>

#include "ImageUploaders/ImageUploader.h"

namespace Ui {
class PictureInfoDialog;
}

class PictureInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit            PictureInfoDialog(QWidget *parent = 0);

                        ~PictureInfoDialog();

    void                SetImage(QPixmap * pPixmap);

    void                showEvent(QShowEvent *);

    void                closeEvent(QCloseEvent *);

private slots:
    void                OnWebServicePopup(bool b);

    void                on_toolButton_2_clicked();

    void                on_toolButton_clicked();

signals:
    void                SavePictureToFile(const QString & strFileName);

private:
    Ui::PictureInfoDialog *ui;

    QPixmap         *   pPixmap;

    QMenu           *   pServicesMenu;

    ImageUploader   *   pImageUploader;


    void                LoadPreview();

    void                CreateWebServicesMenu();
};

#endif // PICTUREINFODIALOG_H
