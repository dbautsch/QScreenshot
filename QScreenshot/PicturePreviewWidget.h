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
