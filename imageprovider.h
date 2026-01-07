#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QtQuick/QQuickImageProvider>
#include <QImage>
#include <preset.h>


class ImageProvider : public QQuickImageProvider

{
public:
    explicit ImageProvider(QList<Preset*> presets) : QQuickImageProvider(QQuickImageProvider::Image)
    {
        this->presets = presets;
    }

    virtual QImage requestImage(const QString &id, QSize *size __attribute__((unused)), const QSize& requestedSize __attribute__((unused)))
    {
        QString rsrcid = ":/" + id;
        Preset *preset = presets.value(id.toInt());
        if (preset == NULL) {
            qCritical() << "Tried to render a preset image but source object was NULL! Returning dummy image.";
            return QImage(256, 30, QImage::Format_RGB888);
        }
        return preset->drawPreview();
    }

    QList<Preset*> presets;
};

#endif // IMAGEPROVIDER_H
