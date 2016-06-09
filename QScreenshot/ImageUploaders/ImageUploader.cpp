#include "ImageUploader.h"

ImageUploader::ImageUploader(QObject *parent) : QObject(parent)
{

}

ServicesList ImageUploader::GetServices()
{
    return ServicesList { "ImageShack.us" };
}

ImageUploader * ImageUploader::CreateInstance(const QString & strServiceName)
{

}
