#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AboutDialog.h"
#include "PictureInfoDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pTray       = new QSystemTrayIcon(this);

    pScreenShot = new ScreenshotCreator(this);

    connect(this, SIGNAL(TakeNewScreenshot(EScreenshotKind)), pScreenShot, SLOT(TakeScreenshot(EScreenshotKind)));
    connect(pScreenShot, SIGNAL(ImageAvailable(QPixmap*)), this, SLOT(NewImageAvailable(QPixmap*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pTray;
    delete pScreenShot;
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

    emit TakeNewScreenshot(EScreenshotKind::EntireScreen);
}

void MainWindow::on_toolButton_3_clicked()
{
    //!<    take a new screenshot - the part of the screen

    emit TakeNewScreenshot(EScreenshotKind::ScreenPart);
}

void MainWindow::NewImageAvailable(QPixmap * pImage)
{
    PictureInfoDialog pictureInfoDialog(this);

    pictureInfoDialog.SetImage(pImage);
    pictureInfoDialog.exec();
}
