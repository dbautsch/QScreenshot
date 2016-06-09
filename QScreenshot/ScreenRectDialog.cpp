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

#include "ScreenRectDialog.h"
#include "ui_ScreenRectDialog.h"
#include "CaptureRectDrawer.h"

#include <QScreen>
#include <QPainter>
#include <QPainterPath>

#define IN_RANGE(val_, minimum_, maximum_) (val_ >= minimum_ && val_ <= maximum_)

ScreenRectDialog::ScreenRectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreenRectDialog)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);

    pTimer              = new QTimer(this);
    pTimer->setInterval(350);
    pTimer->setSingleShot(true);

    connect(pTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));

    bRectEnabled        = false;
    iW                  = 100;
    iH                  = 100;
    rectPos             = QPoint(0, 0);

    pCaptureRectDrawer  = NULL;
}

ScreenRectDialog::~ScreenRectDialog()
{
    delete ui;
}

void ScreenRectDialog::showEvent(QShowEvent * )
{
    currentHitTest  = ERectHitTest::NN;
}

bool ScreenRectDialog::event(QEvent * e)
{
    if (e->type() == QEvent::WindowActivate)
    {
        pTimer->start();
    }

    return QDialog::event(e);
}

void ScreenRectDialog::paintEvent(QPaintEvent * e)
{
    if (bRectEnabled == false)
        return;

    QPainter p(this);

    DrawGrayBackground(&p);
    DrawTransparentRect(&p);
    DrawRectInfo(&p);
}

void ScreenRectDialog::mouseMoveEvent(QMouseEvent * e)
{
    bool bLeftDown          = e->buttons().testFlag(Qt::LeftButton);

    if (bLeftDown == false)
    {
        //  left mouse button is up, nothing to do
        return;
    }

    ERectHitTest hitTest;

    if (currentHitTest == ERectHitTest::NN)
    {
        hitTest             = RectHitTest(e->pos());
        currentHitTest      = hitTest;

        if (hitTest == ERectHitTest::Center)
        {
            iClickDiff_X    = e->pos().x() - rectPos.x();
            iClickDiff_Y    = e->pos().y() - rectPos.y();
        }
    }
    else
    {
        switch (currentHitTest)
        {
        case ERectHitTest::Left:
        {
            int iDiff       = rectPos.x() - e->pos().x();
            rectPos.setX(e->pos().x());
            iW              += iDiff;
            break;
        }

        case ERectHitTest::Top:
        {
            int iDiff       = rectPos.y() - e->pos().y();
            rectPos.setY(e->pos().y());
            iH              += iDiff;
            break;
        }

        case ERectHitTest::Bottom:
        {
            iH                  = e->pos().y() - rectPos.y();
            break;
        }

        case ERectHitTest::Right:
        {
            iW                  = e->pos().x() - rectPos.x();
            break;
        }

        case ERectHitTest::Center:
        {
            rectPos.setX(e->pos().x() - iClickDiff_X);
            rectPos.setY(e->pos().y() - iClickDiff_Y);
            break;
        }

        case ERectHitTest::NN:
        {
            break;
        }
        }

        this->repaint();
    }
}

void ScreenRectDialog::mouseReleaseEvent(QMouseEvent *)
{
    currentHitTest              = ERectHitTest::NN;
    iClickDiff_X                = 0;
    iClickDiff_Y                = 0;
}

void ScreenRectDialog::mouseDoubleClickEvent(QMouseEvent * e)
{
    if (RectHitTest(e->pos()) != ERectHitTest::Center || pCaptureRectDrawer == NULL)
        return;

    QRect r = QRect(rectPos.x(), rectPos.y(), iW, iH);

    pCaptureRectDrawer->CanTakeScreenshoot(r);
}

ERectHitTest ScreenRectDialog::RectHitTest(const QPoint & pt)
{
    ERectHitTest ret    = ERectHitTest::NN;

    if (IN_RANGE(pt.x(), rectPos.x() - 5, rectPos.x() + 5))
        return ERectHitTest::Left;

    if (IN_RANGE(pt.x(), rectPos.x() + iW - 5, rectPos.x() + iW + 5))
        return ERectHitTest::Right;

    if (IN_RANGE(pt.y(), rectPos.y() - 5, rectPos.y() + 5))
        return ERectHitTest::Top;

    if (IN_RANGE(pt.y(), rectPos.y() + iH - 5, rectPos.y() + iH + 5))
        return ERectHitTest::Bottom;

    if (IN_RANGE(pt.x(), rectPos.x() + 6, rectPos.x() + iW - 6) &&
        IN_RANGE(pt.y(), rectPos.y() + 6, rectPos.y() + iH - 6))
    {
        return ERectHitTest::Center;
    }

    return ret;
}

void ScreenRectDialog::DrawGrayBackground(QPainter * p)
{
    /*!
     *  Draw semi-transparent background, with a central fully transparent window (screen part that will
     *  be result image).
     */

    QRect r1, r2, r3, r4;

    QColor color    = QColor(128, 128, 128, 90);

    if (rectPos.x() > 0)
    {
        //  left rect
        r1      = QRect(0, 0, rectPos.x(), this->height());
        p->fillRect(r1, color);
    }

    if (rectPos.y() > 0)
    {
        //  top rect
        r2      = QRect(rectPos.x(), 0, iW, rectPos.y());
        p->fillRect(r2, color);
    }

    if (rectPos.y() + iH < this->height())
    {
        //  bottom rect
        r3      = QRect(rectPos.x(), rectPos.y() + iH, iW, this->height());
        p->fillRect(r3, color);
    }

    if (rectPos.x() + iW < this->width())
    {
        //  right rect
        r4      = QRect(rectPos.x() + iW, 0, this->width(), this->height());
        p->fillRect(r4, color);
    }
}

void ScreenRectDialog::DrawTransparentRect(QPainter * p)
{
    /*!
     *  Draw transparent window and some rulers.
     */

    static const int iMARGIN    = 10;

    QColor semiTransparent      = QColor(255, 255, 255, 5);

    p->fillRect(QRectF(rectPos.x(), rectPos.y(), iW, iH), semiTransparent);

    //  left line
    p->drawLine(QPointF(rectPos.x(), rectPos.y() - iMARGIN), QPointF(rectPos.x(), rectPos.y() + iH + iMARGIN));

    //  top line
    p->drawLine(QPointF(rectPos.x() - iMARGIN, rectPos.y()), QPointF(rectPos.x() + iW + iMARGIN, rectPos.y()));

    //  right line
    p->drawLine(QPointF(rectPos.x() + iW, rectPos.y() - iMARGIN), QPointF(rectPos.x() + iW, rectPos.y() + iH + iMARGIN));

    //  bottom line
    p->drawLine(QPointF(rectPos.x() - iMARGIN, rectPos.y() + iH), QPointF(rectPos.x() + iW + iMARGIN, rectPos.y() + iH));
}

void ScreenRectDialog::DrawRectInfo(QPainter * p)
{
    /*!
    *   Draw some basic information about new screencapture image like width and height
    *   or rect position.
    */

    QString strText = QString::number(iW) + " x " + QString::number(iH);

    QFont oldFont   = p->font();
    QFont newFont   = oldFont;

    newFont.setFamily("Verdana");
    newFont.setPixelSize(16);
    newFont.setBold(true);

    p->setFont(newFont);

    QPoint pos;

    QFontMetrics fm = p->fontMetrics();
    int iLenPX      = fm.width(strText);
    int iHeightPX   = fm.height();

    if (rectPos.x() + iW + iLenPX + 10 > this->width())
    {
        //  move text to left
        if (rectPos.x() - iLenPX - 5 < 0)
        {
            //  move text inside rect
            pos.setX(rectPos.x() + 5);
        }
        else
        {
            pos.setX(rectPos.x() - iLenPX - 5);
        }
    }
    else
    {
        pos.setX(rectPos.x() + iW + 5);
    }

    if (rectPos.y() + iHeightPX + 5 > this->height())
    {
        //  move text to bottom
        if (rectPos.y() - 5 - iHeightPX < 0)
        {
            //  move text inside rect
            pos.setY(rectPos.y() + 5 + iHeightPX);
        }
        else
        {
            pos.setY(rectPos.y() - 5 - iHeightPX);
        }
    }
    else
    {
        pos.setY(rectPos.y() + 5);
    }

    QPen pen;

    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    pen.setBrush(Qt::black);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setColor(Qt::white);

    QPainterPath path;

    p->setFont(newFont);
    p->setPen(pen);

    path.addText(pos.x(), pos.y(), newFont, strText);
    p->drawPath(path);
}

void ScreenRectDialog::OnTimer()
{
    QScreen * s = QApplication::primaryScreen();
    this->setGeometry(s->virtualGeometry());
}

void ScreenRectDialog::EnableRect()
{
    bRectEnabled    = true;
}

void ScreenRectDialog::DisableRect()
{
    bRectEnabled    = false;
}

void ScreenRectDialog::SetRectPos(const QPoint &pt)
{
    rectPos = pt;
}

void ScreenRectDialog::SetRectSize(int iW, int iH)
{
    this->iW = iW;
    this->iH = iH;
}

void ScreenRectDialog::SetRectDrawer(CaptureRectDrawer * pCaptureRectDrawer)
{
    this->pCaptureRectDrawer = pCaptureRectDrawer;
}
