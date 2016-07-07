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

#include "PostImageOrgUploader.h"

PostImageOrgUploader::PostImageOrgUploader(QObject *Parent)
    : ImageUploader(Parent)
{
    strLogoResourcePath = ":/services-thumbnails/postimage.org.png";
}

void PostImageOrgUploader::UploadImage(QPixmap * pPixmap)
{

}

QPixmap PostImageOrgUploader::GetServiceThumbnail()
{
    return QPixmap(":/services-thumbnails/postimage.org.png");
}

QString PostImageOrgUploader::GetServiceName()
{
    return QString("postimage.org");
}

bool PostImageOrgUploader::CanUseLoginData()
{
    return true;
}

bool PostImageOrgUploader::NeedLoginData()
{
    return false;
}
