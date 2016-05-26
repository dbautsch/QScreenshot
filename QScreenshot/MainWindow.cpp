#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AboutDialog.h"
#include "PictureInfoDialog.h"

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
        return;

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
