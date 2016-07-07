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

#ifndef POSTIMAGEORGUPLOADER_H
#define POSTIMAGEORGUPLOADER_H

#include <QObject>
#include <QPixmap>

#include "ImageUploader.h"

class PostImageOrgUploader : public ImageUploader
{
public:
                                PostImageOrgUploader(QObject * Parent);

    virtual void                UploadImage(QPixmap * pPixmap);

    virtual QPixmap             GetServiceThumbnail();

    virtual QString             GetServiceName();

    virtual bool                CanUseLoginData();

    virtual bool                NeedLoginData();

signals:

public slots:
};

#endif // POSTIMAGEORGUPLOADER_H
