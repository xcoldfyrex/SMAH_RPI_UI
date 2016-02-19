#ifndef PRESET_H
#define PRESET_H

#include <QMap>

class Preset
{
public:
    Preset(QString name, bool dynamic = false);
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

    void getHSV();
    void addStep(Step step, int key);
    void getStep(int key);

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
    QMap<int,Step> stepMap;

};

#endif // PRESET_H
