#ifndef LOGGER_H
#define LOGGER_H

#include <QtCore>

void systemlogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // LOGGER_H
