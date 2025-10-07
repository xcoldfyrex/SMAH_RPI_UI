#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QtQuick/QQuickImageProvider>
#include <QImage>
#include <QMap>
#include <preset.h>
#include <QDebug>

extern QMap<int, Preset*> g_colorPresetMap;

class ImageProvider : public QQuickImageProvider

{
public:
    explicit ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
    {

    }

    virtual QImage requestImage(const QString &id, QSize *size __attribute__((unused)), const QSize& requestedSize __attribute__((unused)))
    {
        QString rsrcid = ":/" + id;
        Preset *preset = g_colorPresetMap.value(id.toInt()+1);
        return preset->drawPreview();
    }
};

#endif // IMAGEPROVIDER_H
