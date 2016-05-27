#include "ScreenRectDialog.h"
#include "ui_ScreenRectDialog.h"

#include <QScreen>
#include <QPainter>

ScreenRectDialog::ScreenRectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreenRectDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    //setAttribute(Qt::WA_PaintOnScreen);

    pTimer = new QTimer(this);
    pTimer->setInterval(500);
    pTimer->setSingleShot(true);

    connect(pTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));

    bRectEnabled    = false;
    iW              = 10;
    iH              = 10;
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

    bool bUseR1 = false;
    bool bUseR2 = false;
    bool bUseR3 = false;
    bool bUseR4 = false;

    QRect r1, r2, r3, r4;

    if (rectPos.x() > 0)
    {
        bUseR1  = true;
        r1      = QRect(0, 0, rectPos.x(), this->height());
    }

    if (bUseR1)
    {
        p.setBrush(QBrush(QColor(100, 195, 195, 200)));
        p.fillRect(r1, Qt::DotLine);
    }
}

void ScreenRectDialog::OnTimer()
{
    QScreen * pScreen   = QGuiApplication::primaryScreen();

    this->setGeometry(pScreen->virtualGeometry());
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
