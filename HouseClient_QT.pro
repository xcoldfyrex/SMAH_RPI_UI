#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T13:46:04
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HouseClient_QT
TEMPLATE = app


SOURCES += main.cpp\
    zone.cpp \
    w_hsvpalette.cpp \
    w_colorpreview.cpp \
    w_brightnesspalette.cpp \
    w_mainwindow.cpp \
    w_topheader.cpp \
    w_zoneoverview.cpp \
    w_zonechooser.cpp \
    w_zonecontainer.cpp \
    w_lightcontrolcontainer.cpp \
    w_systemlog.cpp \
    network.cpp

HEADERS  += \
    zone.h \
    w_zoneoverview.h \
    w_zonecontainer.h \
    w_mainwindow.h \
    w_lightcontrolcontainer.h \
    w_hsvpalette.h \
    w_colorpreview.h \
    w_topheader.h \
    w_brightnesspalette.h \
    w_zonechooser.h \
    w_systemlog.h \
    network.h

FORMS    += \
    mainwindow.ui \
    lightcontrolwidget.ui \
    w_systemlog.ui
