#ifndef SCREENSHOTCREATOR_H
#define SCREENSHOTCREATOR_H

#include <QObject>

enum class EScreenshotKind
{
    EntireScreen,
    ScreenPart
};

class ScreenshotCreator : public QObject
{
    Q_OBJECT

public:
    ScreenshotCreator(QObject * Parent);

public slots:
    void    TakeScreenshot(EScreenshotKind kind);

signals:
    void    ImageAvailable(QImage * pImage);
};

#endif // SCREENSHOTCREATOR_H
