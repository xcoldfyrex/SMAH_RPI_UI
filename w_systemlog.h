#ifndef W_SYSTEMLOG_H
#define W_SYSTEMLOG_H

#include <QWidget>
#include <QTextEdit>

namespace Ui {
class SystemLogWidget;
}

class SystemLogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemLogWidget(QWidget *parent = 0);
    ~SystemLogWidget();
    static QTextEdit *txtLogger;
    Ui::SystemLogWidget *ui;
};

#endif // W_SYSTEMLOG_H
