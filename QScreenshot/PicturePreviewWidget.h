#ifndef PICTUREPREVIEWWIDGET_H
#define PICTUREPREVIEWWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>

class PicturePreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit    PicturePreviewWidget(QWidget *parent = 0);

    void        LoadImage(QPixmap * pPixmap);

    void        UnloadImage();

    void        paintEvent(QPaintEvent * e);

private:
    QPixmap *   pPixmap;

signals:

public slots:
};

#endif // PICTUREPREVIEWWIDGET_H
