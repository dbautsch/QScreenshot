#include "ScreenRectDialog.h"
#include "ui_ScreenRectDialog.h"

#include <QScreen>
#include <QPainter>

ScreenRectDialog::ScreenRectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreenRectDialog)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);

    pTimer = new QTimer(this);
    pTimer->setInterval(350);
    pTimer->setSingleShot(true);

    connect(pTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));

    bRectEnabled    = false;
    iW              = 100;
    iH              = 100;
    rectPos         = QPoint(0, 0);
}

ScreenRectDialog::~ScreenRectDialog()
{
    delete ui;
}

void ScreenRectDialog::showEvent(QShowEvent * )
{

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

    QRect r1, r2, r3, r4;

    QColor color    = QColor(128, 128, 128, 128);

    if (rectPos.x() > 0)
    {
        //  left rect
        r1      = QRect(0, 0, rectPos.x(), this->height());
        p.fillRect(r1, color);
    }

    if (rectPos.y() > 0)
    {
        //  top rect
        r2      = QRect(rectPos.x(), 0, iW, rectPos.y());
        p.fillRect(r2, color);
    }

    if (rectPos.y() + iH < this->height())
    {
        //  bottom rect
        r3      = QRect(rectPos.x(), rectPos.y() + iH, iW, this->height());
        p.fillRect(r3, color);
    }

    if (rectPos.x() + iW < this->width())
    {
        //  right rect
        r4      = QRect(rectPos.x() + iW, 0, this->width(), this->height());
        p.fillRect(r4, color);
    }
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
