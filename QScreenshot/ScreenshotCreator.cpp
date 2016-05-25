#include "ScreenshotCreator.h"

#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>

ScreenshotCreator::ScreenshotCreator(QObject *Parent)
    : QObject(Parent)
{

}

void ScreenshotCreator::TakeScreenshot(EScreenshotKind kind)
{
    switch (kind)
    {
    case EScreenshotKind::EntireScreen:
        TakeScreenshot_EntireScreen();
        break;

    case EScreenshotKind::ScreenPart:
        Takescreenshot_Part();
        break;
    }
}

void ScreenshotCreator::TakeScreenshot_EntireScreen()
{
    QScreen * pScreen   = QGuiApplication::primaryScreen();

    pPixmap             = new QPixmap(pScreen->grabWindow(0));

    emit ImageAvailable(pPixmap);
}

void ScreenshotCreator::Takescreenshot_Part()
{

}

void ScreenshotCreator::SaveToFile(const QString & strFileName)
{
    //!<    save current picture to file

    pPixmap->save(strFileName);
}
