#include "PostImageOrgUploader.h"

PostImageOrgUploader::PostImageOrgUploader(QObject *Parent)
    : ImageUploader(Parent)
{

}

void PostImageOrgUploader::UploadImage(QPixmap         * pPixmap,
                                       const QString   & strUserName,
                                       const QString   & strPassword)
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
