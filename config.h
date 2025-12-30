#ifndef CONFIG_H
#define CONFIG_H

#include <QDomDocument>

void loadActions();
void loadZones();
void loadPresets();
void loadScenes();
QDomDocument validateConfigFile(QString config);


#endif // CONFIG_H
