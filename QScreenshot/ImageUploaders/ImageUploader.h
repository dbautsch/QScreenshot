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

#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

#include <QObject>
#include <QList>

enum class EUploadStatus
{
    GeneralError,
    Success
};

typedef QList < QString > ServicesList;

class ImageUploader : public QObject
{
private:
    Q_OBJECT

protected:
    QString                     strLogoResourcePath;

    QString                     strLogin, strPassword;

public:
    explicit                    ImageUploader(QObject *parent = 0);

    virtual void                UploadImage(QPixmap         * pPixmap,
                                            const QString   & strUserName,
                                            const QString   & strPassword)  = 0;

    virtual QPixmap             GetServiceThumbnail()                       = 0;

    virtual QString             GetServiceName()                            = 0;

    virtual bool                CanUseLoginData()                           = 0;    //!<    returns true if this service can use login/password data

    virtual bool                NeedLoginData()                             = 0;    //!<    returns true if this service requires to enter login/password data

    QString                     LogoResourcePath();

    void                        SetLoginPassword(const QString & strLogin, const QString & strPassword);


    static ServicesList         GetServices();

    static ImageUploader    *   CreateInstance(const QString & strServiceName);

signals:
    void                        UploadStatus(EUploadStatus status);

    void                        UploadProgress(unsigned uBytesSent, unsigned uBytesTotal);

public slots:
};

#endif // IMAGEUPLOADER_H
