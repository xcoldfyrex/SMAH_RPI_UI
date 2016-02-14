#include "w_systemlog.h"

#ifndef LOGGER_H
#define LOGGER_H

extern QTextEdit *txtLogger;
extern SystemLogWidget *systemLogWidget;

class Logger : public QObject
{
    Q_OBJECT
    static Logger* instance();

public:
    explicit Logger(QObject *parent = 0);
    void logMessage(QtMsgType type, const char* msg);

signals:

public slots:
};

#endif // LOGGER_H
