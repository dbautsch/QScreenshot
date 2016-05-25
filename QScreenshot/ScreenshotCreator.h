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
    void        TakeScreenshot(EScreenshotKind kind);

    void        SaveToFile(const QString & strFileName);

private:
    QPixmap *   pPixmap;

    void        TakeScreenshot_EntireScreen();

    void        Takescreenshot_Part();

signals:
    void        ImageAvailable(QPixmap * pImage);
};

#endif // SCREENSHOTCREATOR_H
