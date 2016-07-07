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
#include "SignInDialog.h"

#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>

PictureInfoDialog::PictureInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureInfoDialog)
{
    ui->setupUi(this);

    pPixmap             = NULL;
    pServicesMenu       = NULL;
    pImageUploader      = NULL;
    pPasswordsShelter   = NULL;

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

    //  !TODO!
}

void PictureInfoDialog::SetImage(QPixmap * pPixmap)
{
    this->pPixmap = pPixmap;
}

void PictureInfoDialog::SetPasswordsShelter(PasswordsShelter * pPasswordsShelter)
{
    this->pPasswordsShelter = pPasswordsShelter;
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
        bool bCanUpload = false;

        if (pImageUploader->CanUseLoginData())
        {
            QString strLogin, strPassword;

            //  this service can use login/password to access private account data
            if (pPasswordsShelter->GetLoginPasswordForService(pImageUploader->GetServiceName(), strLogin, strPassword)
                == false)
            {
                //  show passwords shelter new login/password dialog
                ServiceExtraData sed;
                bool bShowDialog    = false;

                bool bSED_OK        = pPasswordsShelter->GetServiceExtraData(pImageUploader->GetServiceName(), sed);

                if (sed.bAskForLoginData == false)
                {
                    if (pImageUploader->NeedLoginData())
                    {
                        //  this service need a correct login/password pair
                        QMessageBox::information(this, tr("Image upload"), tr("This web service need login/password. Please set login and password first."));
                        bShowDialog = true;
                    }
                }
                else
                {
                    bShowDialog     = true;
                }

                bool bUsePasswordsShelter   = false;

                if (bShowDialog)
                {
                    SignInDialog signInDialog(this);

                    signInDialog.ShowUseLoginPasswordBox(pImageUploader->NeedLoginData() == false);
                    signInDialog.SetServiceLogo(pImageUploader->LogoResourcePath());

                    signInDialog.exec();

                    QString strLogin = signInDialog.LoginInputBox();
                    QString strPassword = signInDialog.PasswordInputBox();

                    if (strLogin.trimmed().isEmpty() || strPassword.isEmpty())
                    {
                        //  user did not filled all required fields.
                        return;
                    }

                    if (signInDialog.UsePasswordsShelter())
                    {
                        //  saving password into the vault
                        pPasswordsShelter->SetLoginPasswordForService(pImageUploader->GetServiceName(), strLogin, strPassword);
                        bUsePasswordsShelter    = true;
                    }

                    bCanUpload                  = true;
                    pImageUploader->SetLoginPassword(strLogin, strPassword);
                }

                if (bSED_OK == false)
                {
                    //  service extra data was not found - save extra data into passwords shelter
                    sed.bAskForLoginData        = bUsePasswordsShelter;

                    pPasswordsShelter->SetServiceExtraData(pImageUploader->GetServiceName(), sed);
                }
            }
            else
            {
                //  login/password data has been successfully read
                bCanUpload                      = true;
                pImageUploader->SetLoginPassword(strLogin, strPassword);
            }
        }
        else
        {
            //  this service doesn't need login data (may be optional, can be set using password shelter dialog)
            bCanUpload                          = true;
        }

        if (bCanUpload)
        {
            //  now uploading the picture
            pImageUploader->UploadImage(pPixmap);
        }
    }
}
