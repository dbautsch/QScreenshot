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
    Q_OBJECT
public:
    explicit                    ImageUploader(QObject *parent = 0);

    virtual void                UploadImage(QPixmap         * pPixmap,
                                            const QString   & strUserName,
                                            const QString   & strPassword)  = 0;

    virtual QPixmap             GetServiceThumbnail()                       = 0;

    virtual QString             GetServiceName()                            = 0;


    static ServicesList         GetServices();

    static ImageUploader    *   CreateInstance(const QString & strServiceName);

signals:
    void                        UploadStatus(EUploadStatus status);

    void                        UploadProgress(unsigned uBytesSent, unsigned uBytesTotal);

public slots:
};

#endif // IMAGEUPLOADER_H
