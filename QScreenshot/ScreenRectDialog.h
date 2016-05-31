#ifndef SCREENRECTDIALOG_H
#define SCREENRECTDIALOG_H

#include <QDialog>
#include <QEvent>
#include <QTimer>
#include <QPaintEvent>

namespace Ui {
class ScreenRectDialog;
}

class ScreenRectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit                    ScreenRectDialog(QWidget *parent = 0);

                                ~ScreenRectDialog();

    void                        showEvent(QShowEvent * );

    bool                        event(QEvent * e);

    void                        paintEvent(QPaintEvent * e);

    void                        EnableRect();

    void                        DisableRect();

    void                        SetRectPos(const QPoint & pt);

    void                        SetRectSize(int iW, int iH);

private:
    bool                        bRectEnabled;

    Ui::ScreenRectDialog    *   ui;

    QTimer                  *   pTimer;

    QPoint                      rectPos;

    int                         iW, iH; // rect width & height


    void                        DrawGrayBackground(QPainter * p);

    void                        DrawTransparentRect(QPainter * p);

    void                        DrawRectInfo(QPainter * p);

private slots:
    void                        OnTimer();
};

#endif // SCREENRECTDIALOG_H
