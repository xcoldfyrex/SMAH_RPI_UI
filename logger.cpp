#include "logger.h"
#include "w_systemlog.h"

Logger::Logger(QObject *parent) : QObject(parent)
{

}

void Logger::logMessage(QtMsgType type, const char* msg) {
    time_t     now = time(0);
    struct tm  tstruct;
    char       timeString[80];
    tstruct = *localtime(&now);

    strftime(timeString, sizeof(timeString), "[%m-%d-%y %H:%M:%S] ", &tstruct);
    //Ui ui = systemLogWidget->ui;
    //systemLogWidget->txtLogger
    //systemLogWidget->txtLogger->setText(systemLogWidget->txtLogger->toPlainText() + "\n" + timeString + msg);
}
