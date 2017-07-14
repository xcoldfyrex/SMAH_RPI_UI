#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T13:46:04
#
#-------------------------------------------------

QT       += core gui network widgets xml
# CONFIG += console

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = SMAH_RPI_UI
TEMPLATE = app


SOURCES += main.cpp\
    zone.cpp \
    w_colorpreview.cpp \
    w_mainwindow.cpp \
    w_topheader.cpp \
    w_zoneoverview.cpp \
    w_zonechooser.cpp \
    w_zonecontainer.cpp \
    w_lightcontrolcontainer.cpp \
    w_systemlog.cpp \
    network.cpp \
    w_presetchooser.cpp \
    w_zonecontainerheader.cpp \
    w_scheduledactions.cpp \
    w_zoneenvironment.cpp \
    w_hsvwheel.cpp \
    w_hslswatch.cpp

HEADERS  += \
    zone.h \
    w_zoneoverview.h \
    w_zonecontainer.h \
    w_mainwindow.h \
    w_lightcontrolcontainer.h \
    w_hsvpalette.h \
    w_colorpreview.h \
    w_topheader.h \
    w_zonechooser.h \
    w_systemlog.h \
    network.h \
    w_presetchooser.h \
    w_zonecontainerheader.h \
    w_scheduledactions.h \
    w_zoneenvironment.h \
    w_hslswatch.h

FORMS    += \
    mainwindow.ui \
    lightcontrolwidget.ui \
    w_systemlog.ui

DEFINES += QT_MESSAGELOGCONTEXT

INCLUDEPATH += $$PWD/../_lib
DEPENDPATH += $$PWD/../_lib

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/arm/ -lSMAH
unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/x86_64/ -lSMAH

INCLUDEPATH += $$PWD/../../libSMAH/src
DEPENDPATH += $$PWD/../../libSMAH/src
