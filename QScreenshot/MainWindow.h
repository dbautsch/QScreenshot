#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "ScreenshotCreator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void                    NewImageAvailable(QPixmap *pImage);

    void                    on_toolButton_clicked();

    void                    on_toolButton_2_clicked();

    void                    on_toolButton_3_clicked();

signals:
    void                    TakeNewScreenshot(EScreenshotKind kind);

private:
    Ui::MainWindow      *   ui;

    QSystemTrayIcon     *   pTray;

    ScreenshotCreator   *   pScreenShot;
};

#endif // MAINWINDOW_H
