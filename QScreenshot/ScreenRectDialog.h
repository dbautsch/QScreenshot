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

#ifndef SCREENRECTDIALOG_H
#define SCREENRECTDIALOG_H

#include <QDialog>
#include <QEvent>
#include <QTimer>
#include <QPaintEvent>
#include <QMouseEvent>

namespace Ui {
class ScreenRectDialog;
}

class CaptureRectDrawer;

enum class ERectHitTest
{
    NN,
    Left,
    Right,
    Top,
    Bottom,
    Center
};

class ScreenRectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit                    ScreenRectDialog(QWidget *parent = 0);

                                ~ScreenRectDialog();

    void                        showEvent(QShowEvent * );

    bool                        event(QEvent * e);

    void                        paintEvent(QPaintEvent * e);

    void                        mouseMoveEvent(QMouseEvent * e);

    void                        mouseReleaseEvent(QMouseEvent *);

    void                        mouseDoubleClickEvent(QMouseEvent * e);

    void                        EnableRect();

    void                        DisableRect();

    void                        SetRectPos(const QPoint & pt);

    void                        SetRectSize(int iW, int iH);

    void                        SetRectDrawer(CaptureRectDrawer * pCaptureRectDrawer);

private:
    CaptureRectDrawer       *   pCaptureRectDrawer;

    bool                        bRectEnabled;

    Ui::ScreenRectDialog    *   ui;

    QTimer                  *   pTimer;

    QPoint                      rectPos;

    int                         iW, iH; // rect width & height

    int                         iClickDiff_X, iClickDiff_Y;

    ERectHitTest                currentHitTest;


    void                        DrawGrayBackground(QPainter * p);

    void                        DrawTransparentRect(QPainter * p);

    void                        DrawRectInfo(QPainter * p);

    ERectHitTest                RectHitTest(const QPoint & pt);

private slots:
    void                        OnTimer();
};

#endif // SCREENRECTDIALOG_H
