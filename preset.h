#ifndef PRESET_H
#define PRESET_H

#include <QMap>
#include <QString>
#include <QLinearGradient>
#include <QPainter>
#include <QImage>
#include <QObject>

class Preset : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT);
    Q_PROPERTY(QString hex READ getHex CONSTANT);
    Q_PROPERTY(QImage image READ drawPreview CONSTANT);


public:
    Q_INVOKABLE
    Preset(QString name, bool dynamic = false, int fade = 0, int delay = 10, int type = 1);
    Preset(QString name, QString code);
    class Step {
    public:
        void getHSV();
        int h;
        int s;
        int v;
    };
    class Offset {
    public:
        QString colorHex;
        int start;
        int end;
        int skip;
    };
    int getDelay();
    QString getHex();
    void addStep(Step *step, int key);
    void getStep(int key);
    void addOffset(Offset *offset, int key);
    void getOffset(int key);
    int delay;
    int fade;
    int r;
    int g;
    int b;
    int type;
    int w;
    QMap<int, Step*> getSteps();
    QMap<int, Offset*> getOffsets();

    void setColor(QString color);
    QString getName();
    bool dynamic;
    QImage drawPreview();

private:
    QString name;
    QString colorHex;
    QMap<int,Step*> stepMap;
    QMap<int,Offset*> offsetMap;
};

#endif // PRESET_H
