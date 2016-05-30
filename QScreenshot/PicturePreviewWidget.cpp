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

#include "PicturePreviewWidget.h"

#include <QPaintEngine>
#include <QPainter>
#include <QDebug>

#define IMAGE_MARGIN_PX    10

PicturePreviewWidget::PicturePreviewWidget(QWidget *parent) : QWidget(parent)
{
    pPixmap = NULL;
}

void PicturePreviewWidget::paintEvent(QPaintEvent * e)
{
    /*!
      * Draw preview of the screenshot. Center image vertically and horizontally
      * using simple calculation.
      */

    if (pPixmap == NULL)
        return;

    QPainter p(this);

    QRectF rcSource, rcTarget;

    rcSource.setX(0);
    rcSource.setY(0);
    rcSource.setWidth(pPixmap->width());
    rcSource.setHeight(pPixmap->height());

    double dRatio1  = static_cast<double>(pPixmap->height()) / static_cast<double>(pPixmap->width());

    double dWidth   = e->rect().width();
    double dHeight  = dWidth * dRatio1;

    if (dHeight > e->rect().height())
    {
        //  recalculating

        double dRatio2  = static_cast<double>(pPixmap->width()) / static_cast<double>(pPixmap->height());

        dHeight     = e->rect().height();
        dWidth      = dHeight * dRatio2;
    }

    double dMarginLeft  = (e->rect().width() - dWidth) / 2.0;
    double dMarginTop   = (e->rect().height() - dHeight) / 2.0;

    rcTarget.setX(dMarginLeft);
    rcTarget.setY(dMarginTop);
    rcTarget.setWidth(dWidth);
    rcTarget.setHeight(dHeight);

    p.setRenderHint(QPainter::Antialiasing);
    p.drawPixmap(rcTarget, * pPixmap, rcSource);
}

void PicturePreviewWidget::LoadImage(QPixmap * pPixmap)
{
    this->pPixmap = pPixmap;
}

void PicturePreviewWidget::UnloadImage()
{
    pPixmap = NULL;
}
