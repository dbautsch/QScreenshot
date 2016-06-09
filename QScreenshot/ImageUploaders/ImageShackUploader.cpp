#include "ImageShackUploader.h"

ImageShackUploader::ImageShackUploader(QObject *parent)
    : ImageUploader(parent)
{

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
