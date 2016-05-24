#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AboutDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pTray   = new QSystemTrayIcon(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    //!<    about click

    AboutDialog ad;

    ad.exec();
}
