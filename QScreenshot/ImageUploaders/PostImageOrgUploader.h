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
