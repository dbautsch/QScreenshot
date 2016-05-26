#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

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

    void                    closeEvent(QCloseEvent * e);

private slots:
    void                    NewImageAvailable(QPixmap *pImage);

    void                    OnTrayShowProgramClick();

    void                    OnTrayQuitProgramClick();

    void                    OnTraySettingsClick();

    void                    OnTrayActivated(QSystemTrayIcon::ActivationReason reason);

    void                    on_toolButton_clicked();

    void                    on_toolButton_2_clicked();

    void                    on_toolButton_3_clicked();

signals:
    void                    TakeNewScreenshot(EScreenshotKind kind);

private:
    Ui::MainWindow      *   ui;

    QSystemTrayIcon     *   pTray;

    QMenu               *   pTrayMenu;

    ScreenshotCreator   *   pScreenShot;

    QAction             *   pShowHideProgramAction;

    QAction             *   pQuitProgramAction;

    QAction             *   pSettingsAction;

    bool                    bCanClose;


    void                    CreateTrayIcon();
};

#endif // MAINWINDOW_H
