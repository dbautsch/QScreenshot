#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

enum class EUploadStatus
{
    GeneralError,
    Success
};

class ImageUploader : public QObject
{
    Q_OBJECT
public:
    explicit            ImageUploader(QObject *parent = 0);

    virtual void        UploadImage(QPixmap         * pPixmap,
                                    const QString   & strUserName,
                                    const QString   & strPassword)  = 0;

    virtual QPixmap     GetServiceThumbnail()                       = 0;

    virtual QString     GetServiceName()                            = 0;

signals:
    void                UploadStatus(EUploadStatus status);

    void                UploadProgress(unsigned uBytesSent, unsigned uBytesTotal);

public slots:
};

#endif // IMAGEUPLOADER_H
