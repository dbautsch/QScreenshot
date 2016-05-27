#ifndef CAPTURERECTDRAWER_H
#define CAPTURERECTDRAWER_H

#include <QObject>

class CaptureRectDrawer : public QObject
{
    Q_OBJECT
public:
    explicit CaptureRectDrawer(QObject *parent = 0);

signals:

public slots:
};

#endif // CAPTURERECTDRAWER_H
