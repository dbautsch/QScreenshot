#ifndef POSTIMAGEORGUPLOADER_H
#define POSTIMAGEORGUPLOADER_H

#include <QObject>
#include <QPixmap>

#include "ImageUploader.h"

class PostImageOrgUploader : public ImageUploader
{
public:
                                PostImageOrgUploader(QObject * Parent);

    virtual void                UploadImage(QPixmap         * pPixmap,
                                            const QString   & strUserName,
                                            const QString   & strPassword);

    virtual QPixmap             GetServiceThumbnail();

    virtual QString             GetServiceName();

signals:

public slots:
};

#endif // POSTIMAGEORGUPLOADER_H
