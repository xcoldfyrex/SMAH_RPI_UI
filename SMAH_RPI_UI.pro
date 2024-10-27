#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T13:46:04
#
#-------------------------------------------------

QT       += core gui network widgets xml quick quickwidgets sql
CONFIG   += console
CONFIG   += debug

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = SMAH_RPI_UI
TEMPLATE = app


SOURCES += main.cpp\
    commandrouter.cpp \
    dbmanager.cpp \
    mainwindow.cpp \
    rpidevice.cpp \
    shellyrgbw.cpp \
    widgets/w_hsvwheel.cpp \
    widgets/w_powercontrol.cpp \
    widgets/w_scheduledactions.cpp \
    logger.cpp \
    preset.cpp \
    datagramhandler.cpp \
    light.cpp \
    tcpsocket.cpp \
    presettask.cpp \
    zone.cpp \
    zwavemanager.cpp \
    sunriseset.cpp \
    sensor.cpp \
    ui_mainwindow.cpp \
    rsslisting.cpp \
    tcpconnectionfactory.cpp \
    zwaveworker.cpp



HEADERS  += \
    dbmanager.h \
    imageprovider.h \
    mainwindow.h \
    rpidevice.h \
    shellyrgbw.h \
    widgets/w_hsvpalette.h \
    widgets/w_powercontrol.h \
    widgets/w_scheduledactions.h \
    build_number.h \
    logger.h \
    preset.h \
    datagramhandler.h \
    light.h \
    build_number.h \
    logger.h \
    presettask.h \
    tcpsocket.h \
    zone.h \
    zwavemanager.h \
    sunriseset.h \
    widgets/w_screensaver.h \
    eventfilter.h \
    sensor.h \
    commandrouter.h \
    ui_mainwindow.h \
    rsslisting.h \
    tcpconnectionfactory.h \
    zwaveworker.h


FORMS    += \
    ui_mainwindow.ui \
    weatherwidget.ui

DEFINES += QT_MESSAGELOGCONTEXT


INCLUDEPATH += $$PWD/../_lib
DEPENDPATH += $$PWD/../_lib

#unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/arm/ -lSMAH
#unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/x86_64/ -lSMAH

#INCLUDEPATH += $$PWD/../../libSMAH/src
#DEPENDPATH += $$PWD/../../libSMAH/src

build_nr.commands = ../build_number.sh
build_nr.depends = FORCE
QMAKE_EXTRA_TARGETS += build_nr
PRE_TARGETDEPS += build_nr

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/arm/ -lopenzwave
unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib64/ -lopenzwave

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib/arm/ -lpigpio
unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/lib64/ -lpigpio


INCLUDEPATH += $$PWD/../../../../../usr/local/include/openzwave
DEPENDPATH += $$PWD/../../../../../usr/local/include/openzwave

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

DISTFILES += \
    ../../../../../usr/local/include/openzwave/aes/aes.txt


RESOURCES += qml.qrc
# QMAKE_CXXFLAGS += "-fno-sized-deallocation"
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =
