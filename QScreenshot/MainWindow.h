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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QTimer>

#include "ScreenshotCreator.h"
#include "SettingsDialog.h"

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

    void                    OnShowHideTimer();

    void                    on_toolButton_clicked();

    void                    on_toolButton_2_clicked();

    void                    on_toolButton_3_clicked();

    void                    on_toolButton_4_clicked();

public slots:
    void                    RestoreApplicationGeometry(const QPoint & ptPos);

signals:
    void                    TakeNewScreenshot(EScreenshotKind kind);

    void                    SaveApplicationGeometry(const QPoint & ptPos);

private:
    Ui::MainWindow      *   ui;

    QSystemTrayIcon     *   pTray;

    QMenu               *   pTrayMenu;

    ScreenshotCreator   *   pScreenShot;

    SettingsDialog      *   pSettings;

    QAction             *   pShowHideProgramAction;

    QAction             *   pQuitProgramAction;

    QAction             *   pSettingsAction;

    QTimer              *   pShowHideTimer;

    bool                    bCanClose;

    EScreenshotKind         screenshotKind;


    void                    CreateTrayIcon();
};

#endif // MAINWINDOW_H
