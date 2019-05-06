#ifndef QENGRAVEDLABEL_H
#define QENGRAVEDLABEL_H

#include <QRect>
#include <QLabel>
#include <QListWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsEffect>
#include <QPushButton>

class QEngravedLabel : public QLabel
{
public:

    explicit QEngravedLabel(QWidget *parent= Q_NULLPTR, Qt::WindowFlags f=Q_NULLPTR)
        : QLabel(parent, f){
        QGraphicsDropShadowEffect* eff = new QGraphicsDropShadowEffect(this);
        eff->setBlurRadius(2);
        eff->setXOffset(2);
        eff->setYOffset(2);
        eff->setColor(QColor("#111111"));
        this->setGraphicsEffect(eff);
    }
    explicit QEngravedLabel(const QString &text, QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Q_NULLPTR)
        : QLabel(text,parent,f){
        QGraphicsDropShadowEffect* eff = new QGraphicsDropShadowEffect(this);
        eff->setBlurRadius(2);
        eff->setXOffset(2);
        eff->setYOffset(2);
        eff->setColor(QColor("#111111"));
        this->setGraphicsEffect(eff);
    }

protected:

};

class QEngravedPushButton: public QPushButton
{
public:

    explicit QEngravedPushButton(QWidget *parent= Q_NULLPTR)
        : QPushButton(parent){
        QGraphicsDropShadowEffect* eff = new QGraphicsDropShadowEffect(this);
        eff->setBlurRadius(2);
        eff->setXOffset(2);
        eff->setYOffset(2);
        eff->setColor(QColor("#111111"));
        this->setGraphicsEffect(eff);
    }
    explicit QEngravedPushButton(const QString &text, QWidget *parent=Q_NULLPTR)
        : QPushButton(text,parent){
        QGraphicsDropShadowEffect* eff = new QGraphicsDropShadowEffect(this);
        eff->setBlurRadius(2);
        eff->setXOffset(2);
        eff->setYOffset(2);
        eff->setColor(QColor("#111111"));
        this->setGraphicsEffect(eff);
    }

protected:

};

class QEngravedList : public QListWidget
{
public:

    explicit QEngravedList(QWidget *parent= Q_NULLPTR)
        : QListWidget(parent){
        //QGraphicsDropShadowEffect* eff = new QGraphicsDropShadowEffect(this);
        //eff->setBlurRadius(2);
        //eff->setXOffset(2);
        //eff->setYOffset(2);
        //eff->setColor(QColor("#111111"));
        //this->setGraphicsEffect(eff);
    }

protected:

};

#endif // QENGRAVEDLABEL_H
