#ifndef PRESET_H
#define PRESET_H

#include <QMap>

class Preset
{
public:
    Preset(QString name, short id, bool dynamic = false);
    class Step {
    public:
        void getHSV();

        struct stepHSV {
            short h;
            short s;
            short v;
        };

    private:
        int delay;

    };

    QString getHex();
    void addStep(Step step, int key);
    void getStep(int key);
    short id;

    QMap<int,Step> getSteps();
    void setColor(QString color);
    QString getName();

private:
    bool dynamic;
    int delay;
    short r;
    short g;
    short b;
    short w;
    QString name;
    QString colorHex;
    QMap<int,Step> stepMap;

};

#endif // PRESET_H
