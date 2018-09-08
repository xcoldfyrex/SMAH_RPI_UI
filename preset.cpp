#include "preset.h"

Preset::Preset(QString name, short id, bool dynamic, int fade, int delay, int type)
{
    this->name = name;
    this->dynamic = dynamic;
    this->id = id;
    this->fade = fade;
    this->delay = delay;
    this->type = type;
}

Preset::Preset()
{

}

QMap<int, Preset::Step *> Preset::getSteps()
{
    return this->stepMap;
}

QMap<int, Preset::Offset *> Preset::getOffsets()
{
    return this->offsetMap;
}

void Preset::setColor(QString color)
{
    bool ok;
    this->r = color.mid(0,2).toInt(&ok, 16);
    this->g = color.mid(2,2).toInt(&ok, 16);
    this->b = color.mid(4,2).toInt(&ok, 16);
    this->w = color.mid(6,2).toInt(&ok, 16);
    this->colorHex = color;
}

QString Preset::getName()
{
    return this->name;
}

QString Preset::getHex()
{
    return this->colorHex;
}

void Preset::addStep(Step *step, int key)
{
    this->stepMap.insert(key,step);
}

void Preset::addOffset(Offset *offset, int key)
{
    this->offsetMap.insert(key,offset);
}

int Preset::getID()
{
    return this->id;
}

int Preset::getDelay()
{
    return this->delay;
}

QImage Preset::drawPreview()
{
    if (dynamic)
    {
        QImage canvas(getSteps().size() * 256, 100, QImage::Format_RGB888);
        QPainter canvasPainter(&canvas);

        for (int currentStep = 0; currentStep < getSteps().size(); currentStep++) {
            int nextStep = 0;
            if (currentStep < (getSteps().size()) -1)
                nextStep = currentStep + 1;
            Preset::Step *baseStep;
            Preset::Step *targetStep;

            QLinearGradient fade(QPointF(0,0), QPointF(256, 0));
            baseStep = getSteps().value(currentStep);
            targetStep = getSteps().value(nextStep);

            fade.setColorAt(0, QColor(baseStep->h, baseStep->s, baseStep->v));
            fade.setColorAt(1, QColor(targetStep->h, targetStep->s, targetStep->v));

            QImage image(256, 100, QImage::Format_RGB888);
            QPainter painter(&image);
            painter.fillRect(image.rect(),fade);
            canvasPainter.drawImage(256, 0, image);
        }
        return canvas;
    } else {
        QImage canvas(256, 100, QImage::Format_RGB888);
        canvas.fill(QColor::fromRgb(r,g,b));
        return canvas;
    }
}
