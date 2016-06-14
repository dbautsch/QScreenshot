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

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AboutDialog.h"
#include "PictureInfoDialog.h"

#include "PasswordsShelter.h"

#include <QScreen>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bCanClose   = false;

    pShowHideTimer  = new QTimer(this);
    pShowHideTimer->setInterval(300);
    pShowHideTimer->setSingleShot(true);
    connect(pShowHideTimer, SIGNAL(timeout()), this, SLOT(OnShowHideTimer()));

    pScreenShot = new ScreenshotCreator(this);

    connect(this, SIGNAL(TakeNewScreenshot(EScreenshotKind)), pScreenShot, SLOT(TakeScreenshot(EScreenshotKind)));
    connect(pScreenShot, SIGNAL(ImageAvailable(QPixmap*)), this, SLOT(NewImageAvailable(QPixmap*)));

    CreateTrayIcon();

    pSettings   = new SettingsDialog(this);
    pSettings->setModal(true);

    connect(this, SIGNAL(SaveApplicationGeometry(QPoint)), pSettings, SLOT(SaveApplicationGeometry(QPoint)));
    connect(pSettings, SIGNAL(RestoreApplicationGeometry(QPoint)), this, SLOT(RestoreApplicationGeometry(QPoint)));

    pSettings->ReadSettings();

    PasswordsShelter p;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pTray;
    delete pScreenShot;
    delete pTrayMenu;
}

void MainWindow::closeEvent(QCloseEvent * e)
{
    if (bCanClose)
    {
        QRect rcGeometry = this->geometry();

        emit SaveApplicationGeometry(QPoint(rcGeometry.left(), rcGeometry.top()));

        return;
    }

    e->ignore();

    this->hide();
    pShowHideProgramAction->setText("Show program");
}

void MainWindow::on_toolButton_clicked()
{
    //!<    about click

    AboutDialog ad;

    ad.exec();
}

void MainWindow::on_toolButton_2_clicked()
{
    //!<    take a new screenshot - the entire screen

    screenshotKind = EScreenshotKind::EntireScreen;

    OnTrayShowProgramClick();
    pShowHideTimer->start();
}

void MainWindow::on_toolButton_3_clicked()
{
    //!<    take a new screenshot - the part of the screen

    screenshotKind = EScreenshotKind::ScreenPart;

    OnTrayShowProgramClick();
    pShowHideTimer->start();
}

void MainWindow::on_toolButton_4_clicked()
{
    //!<    settings button clicked

    OnTraySettingsClick();
}

void MainWindow::NewImageAvailable(QPixmap * pImage)
{
    /*!
     *  A new picture has been taken.
     *
     *  \param pImage Pointer to the picture object, must be freed
     *  after use.
     */

    OnTrayShowProgramClick();

    PictureInfoDialog pictureInfoDialog(this);

    connect(&pictureInfoDialog, SIGNAL(SavePictureToFile(QString)), pScreenShot, SLOT(SaveToFile(QString)));

    pictureInfoDialog.SetImage(pImage);
    pictureInfoDialog.exec();
}

void MainWindow::CreateTrayIcon()
{
    pTray                   = new QSystemTrayIcon(this);
    pTray->setIcon(QIcon(":/icons/main-icon.png"));
    pTray->setToolTip("QScreenshot - ready");
    pTray->setVisible(true);

    connect(pTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(OnTrayActivated(QSystemTrayIcon::ActivationReason)));

    pTrayMenu               = new QMenu(this);

    pShowHideProgramAction  = pTrayMenu->addAction("Show program", this, SLOT(OnTrayShowProgramClick()));
    pSettingsAction         = pTrayMenu->addAction("Settings", this, SLOT(OnTraySettingsClick()));
    pQuitProgramAction      = pTrayMenu->addAction("Quit", this, SLOT(OnTrayQuitProgramClick()));

    pTray->setContextMenu(pTrayMenu);
}

void MainWindow::OnTrayShowProgramClick()
{
    if (this->isHidden())
    {
        this->show();
        pShowHideProgramAction->setText("Hide program");
    }
    else
    {
        this->hide();
        pShowHideProgramAction->setText("Show program");
    }
}

void MainWindow::OnTrayQuitProgramClick()
{
    bCanClose = true;
    this->close();
}

void MainWindow::OnTraySettingsClick()
{
    pSettings->exec();
}

void MainWindow::OnTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        OnTrayShowProgramClick();
    }
}

void MainWindow::OnShowHideTimer()
{
    emit TakeNewScreenshot(screenshotKind);
}

void MainWindow::RestoreApplicationGeometry(const QPoint & ptPos)
{
    QPoint ptPosOK          = ptPos;
    bool bNeedToSave        = false;

    if (ptPos.x() == std::numeric_limits<int>::min() || ptPos.y() == std::numeric_limits<int>::min())
    {
        QScreen * pScreen   = QGuiApplication::primaryScreen();
        QRect rcGeometry    = this->geometry();

        ptPosOK.setX((pScreen->availableGeometry().width() / 2.0) - (rcGeometry.width() / 2.0));
        ptPosOK.setY((pScreen->availableGeometry().height() / 2.0) - (rcGeometry.height() / 2.0));

        bNeedToSave         = true;
    }

    QRect rcGeometry        = this->geometry();

    this->setGeometry(ptPosOK.x(), ptPosOK.y(), rcGeometry.width(), rcGeometry.height());

    if (bNeedToSave)
        pSettings->SaveApplicationGeometry(ptPosOK);
}
