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

#include "ImageShackUploader.h"

ImageShackUploader::ImageShackUploader(QObject *parent)
    : ImageUploader(parent)
{
    strLogoResourcePath = ":/services-thumbnails/imageshack.us.png";
}

void ImageShackUploader::UploadImage(QPixmap         * pPixmap,
                                     const QString   & strUserName,
                                     const QString   & strPassword)
{

}

QPixmap ImageShackUploader::GetServiceThumbnail()
{
    return QPixmap(":/services-thumbnails/imageshack.us.png");
}

QString ImageShackUploader::GetServiceName()
{
    return "imageshack.us";
}

bool ImageShackUploader::CanUseLoginData()
{
    return true;
}

bool ImageShackUploader::NeedLoginData()
{
    return true;
}
