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

#include "ScreenshotCreator.h"

#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>

ScreenshotCreator::ScreenshotCreator(QObject *Parent)
    : QObject(Parent)
{
    pCaptureRectDrawer = new CaptureRectDrawer(this);

    connect(this, SIGNAL(ShowCaptureRect()), pCaptureRectDrawer, SLOT(ShowRect()));
    connect(pCaptureRectDrawer, SIGNAL(RectSubmited(QRect)), this, SLOT(CaptureRectSubmited(QRect)));
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
    emit ShowCaptureRect();
}

void ScreenshotCreator::SaveToFile(const QString & strFileName)
{
    //!<    save current picture to file

    pPixmap->save(strFileName);
}

void ScreenshotCreator::CaptureRectSubmited(const QRect & r)
{
    /*!
     *  Part of the screen has been submited by user - can
     *  create screenshot using rect r.
     *
     *  \param r Rectangular part of the screen that will be
     *  saved to QPixmap.
     */
}
