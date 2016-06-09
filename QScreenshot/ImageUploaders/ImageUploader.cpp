#include "ImageUploader.h"
#include "ImageShackUploader.h"

ImageUploader::ImageUploader(QObject *parent) : QObject(parent)
{

}

ServicesList ImageUploader::GetServices()
{
    return ServicesList { "ImageShack.us" };
}

ImageUploader * ImageUploader::CreateInstance(const QString & strServiceName)
{
    if (strServiceName == "imageshack.us")
        return new ImageShackUploader(nullptr);

    return nullptr;
}
