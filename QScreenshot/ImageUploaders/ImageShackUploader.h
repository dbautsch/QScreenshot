#ifndef IMAGESHACKUPLOADER_H
#define IMAGESHACKUPLOADER_H

#include <QObject>
#include <QPixmap>
#include <QString>

#include "ImageUploader.h"

class ImageShackUploader : public ImageUploader
{
public:
                                ImageShackUploader(QObject *parent = 0);

    virtual void                UploadImage(QPixmap         * pPixmap,
                                            const QString   & strUserName,
                                            const QString   & strPassword);

    virtual QPixmap             GetServiceThumbnail();

    virtual QString             GetServiceName();
};

#endif // IMAGESHACKUPLOADER_H
