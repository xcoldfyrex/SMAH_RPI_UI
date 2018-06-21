#include "logger.h"

void systemlogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const char* date = QTime::currentTime().toString().toStdString().c_str();
    const char *const green = "\033[1;32m";
    const char *const blue = "\033[1;34m";
    const char *const yellow = "\033[1;33m";
    const char *const red = "\033[1;31m";
    const char *const normal = "\033[0m";
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "%s %s[DEBUG]%s %s (%s:%u, %s)\n", date, blue, normal, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "%s %s[INFO]%s %s\n", date, green, normal, localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "%s %s[WARNING]%s %s\n", date, yellow, normal, localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "%s %s[CRITICAL] %s %s (%s:%u, %s)\n", date, red, normal, localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "%s %s[FATAL] %s %s (%s:%u, %s)\n", date, red, normal, localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}
