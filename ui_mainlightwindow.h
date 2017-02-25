/********************************************************************************
** Form generated from reading UI file 'mainlightwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINLIGHTWINDOW_H
#define UI_MAINLIGHTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainLightWindow
{
public:
    QLabel *label;

    void setupUi(QWidget *MainLightWindow)
    {
        if (MainLightWindow->objectName().isEmpty())
            MainLightWindow->setObjectName(QStringLiteral("MainLightWindow"));
        MainLightWindow->resize(640, 480);
        label = new QLabel(MainLightWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 9, 78, 16));

        retranslateUi(MainLightWindow);

        QMetaObject::connectSlotsByName(MainLightWindow);
    } // setupUi

    void retranslateUi(QWidget *MainLightWindow)
    {
        MainLightWindow->setWindowTitle(QApplication::translate("MainLightWindow", "Form", 0));
        label->setText(QApplication::translate("MainLightWindow", "Select Zone", 0));
    } // retranslateUi

};

namespace Ui {
    class MainLightWindow: public Ui_MainLightWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINLIGHTWINDOW_H
