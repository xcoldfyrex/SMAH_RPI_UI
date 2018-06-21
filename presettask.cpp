#include <QDebug>
#include <QLinearGradient>
#include <QPainter>

#include "presettask.h"


PresetTask::PresetTask(Preset *preset) : QThread(Q_NULLPTR)
{
    this->preset = *preset;
    this->abortFlag = false;
}

void PresetTask::run()
{
    QImage canvas = preset.drawPreview();
    int offset = 0;
    while (!abortFlag)
    {
        if (offset >= canvas.width())
            offset = 0;
        QRgb qrgb = canvas.pixel(offset,0);
        QColor color(qrgb);
        emit colorStepChanged(color);
        this->msleep(preset.getDelay());
        offset++;
    }
}
