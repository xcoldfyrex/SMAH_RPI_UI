#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QtQuick/QQuickImageProvider>
#include <QImage>
#include <QMap>
#include <preset.h>
#include <QDebug>

extern QMap<int, Preset*> gColorPresetMap;

class ImageProvider : public QQuickImageProvider

{
public:
    explicit ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
    {

    }

    virtual QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize)
    {
        QString rsrcid = ":/" + id;
        Preset *preset = gColorPresetMap.value(id.toInt()+1);
        return preset->drawPreview();
    }
};

#endif // IMAGEPROVIDER_H
