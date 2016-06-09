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

#include "PictureInfoDialog.h"
#include "ui_PictureInfoDialog.h"

#include <QFileDialog>
#include <QDateTime>

PictureInfoDialog::PictureInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureInfoDialog)
{
    ui->setupUi(this);

    pPixmap         = NULL;
    pServicesMenu   = NULL;
    pImageUploader  = NULL;

    CreateWebServicesMenu();

    ui->toolButton->setMenu(pServicesMenu);
}

PictureInfoDialog::~PictureInfoDialog()
{
    delete ui;
}

void PictureInfoDialog::showEvent(QShowEvent *)
{
    LoadPreview();
}

void PictureInfoDialog::closeEvent(QCloseEvent *)
{
    ui->widget->UnloadImage();

    delete pPixmap;
    pPixmap = NULL;
}

void PictureInfoDialog::on_toolButton_2_clicked()
{
    //!<    save to file clicked

    QString strNamePattern  = "Screen-" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".png";

    QString strFile         = QFileDialog::getSaveFileName(this,
                                                           "Choose destination for file",
                                                           strNamePattern,
                                                           tr("PNG Files (*.png);;JPEG Files (*.jpg);;BMP Files (*.bmp)"));
    if (strFile.isEmpty())
        return;

    emit SavePictureToFile(strFile);
}

void PictureInfoDialog::on_toolButton_clicked()
{
    //!<    upload to web clicked


}

void PictureInfoDialog::SetImage(QPixmap * pPixmap)
{
    this->pPixmap = pPixmap;
}

void PictureInfoDialog::LoadPreview()
{
    ui->widget->LoadImage(pPixmap);

    ui->label_2->setText(QString::number(pPixmap->width()) + " x " + QString::number(pPixmap->height()));
}

void PictureInfoDialog::CreateWebServicesMenu()
{
    //!<    create popup menu with the list of supported image hosting services

    ServicesList servicesList   = ImageUploader::GetServices();

    if (servicesList.size() == 0)
        return;

    pServicesMenu               = new QMenu(this);

    foreach (const QString & strService, servicesList)
    {
        QAction * pMenuAction   = new QAction(strService, pServicesMenu);
        pMenuAction->setData(strService);

        connect(pMenuAction, SIGNAL(triggered(bool)), this, SLOT(OnWebServicePopup(bool)));

        pServicesMenu->addAction(pMenuAction);
    }
}

void PictureInfoDialog::OnWebServicePopup(bool b)
{
    //!<    a menu item of the image hosting services popup has been clicked

    QObject * pSender   = QObject::sender();

    if (pSender == NULL)
        return;

    QAction * pAction   = dynamic_cast < QAction * > (pSender);

    if (pAction == NULL)
        return;

    if (pImageUploader != NULL)
    {
        delete pImageUploader;
    }

    //  create the instance of the appropriate image uploader
    pImageUploader      = ImageUploader::CreateInstance(pAction->data().toString());

    if (pImageUploader)
    {

    }
}
