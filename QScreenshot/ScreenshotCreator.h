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

#ifndef SCREENSHOTCREATOR_H
#define SCREENSHOTCREATOR_H

#include <QObject>

#include "CaptureRectDrawer.h"

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
    void                    TakeScreenshot(EScreenshotKind kind);

    void                    SaveToFile(const QString & strFileName);

    void                    CaptureRectSubmited(const QRect & r);

private:
    QPixmap             *   pPixmap;

    CaptureRectDrawer   *   pCaptureRectDrawer;


    void                    TakeScreenshot_EntireScreen();

    void                    Takescreenshot_Part();

signals:
    void                    ImageAvailable(QPixmap * pImage);

    void                    ShowCaptureRect();

    void                    HideCaptureRect();
};

#endif // SCREENSHOTCREATOR_H
