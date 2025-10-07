#include "logger.h"

void systemlogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const std::string date = QTime::currentTime().toString().toStdString();
    const std::string day = QDate::currentDate().toString().toStdString();
    const char *const green = "\033[1;32m";
    const char *const blue = "\033[1;34m";
    const char *const yellow = "\033[1;33m";
    const char *const red = "\033[1;31m";
    const char *const normal = "\033[0m";
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "%s %s %s [DEBUG]%s %s (%s:%u, %s)\n", day.c_str(), date.c_str(), blue, normal, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "%s %s %s [INFO]%s %s\n", day.c_str(), date.c_str(), green, normal, localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "%s %s %s [WARNING]%s %s (%s:%u, %s)\n", day.c_str(), date.c_str(), yellow, normal, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "%s %s %s [CRITICAL] %s %s (%s:%u, %s)\n", day.c_str(), date.c_str(), red, normal, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "%s %s %s [FATAL] %s %s (%s:%u, %s)\n", day.c_str(), date.c_str(), red, normal, localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}
