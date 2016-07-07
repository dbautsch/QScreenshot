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
