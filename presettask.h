#ifndef PRESETTASK_H
#define PRESETTASK_H

#include <QThread>
#include <QColor>

#include "preset.h"


class Zone;

class PresetTask : public QThread
{
    Q_OBJECT
public:
    PresetTask(Preset *preset);
    void run();
    bool abortFlag;

private:
    Preset preset;

signals:
    void colorStepChanged(QColor color);

public slots:
};

#endif // PRESETTASK_H
