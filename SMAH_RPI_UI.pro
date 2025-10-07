#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T13:46:04
#
#-------------------------------------------------

QT       += core gui network widgets xml qml quick quickwidgets sql websockets httpserver
CONFIG   += console
CONFIG   += debug

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets charts

TARGET = SMAH_RPI_UI
TEMPLATE = app


SOURCES += main.cpp\
    config.cpp \
    dbmanager.cpp \
    ponddata.cpp \
    rpidevice.cpp \
    scheduled_actions.cpp \
    shellyrgbw.cpp \
    logger.cpp \
    preset.cpp \
    light.cpp \
    presettask.cpp \
    weatherdata.cpp \
    zone.cpp \
    sensor.cpp \
    zwavesocket.cpp



HEADERS  += \
    config.h \
    dbmanager.h \
    imageprovider.h \
    ponddata.h \
    rpidevice.h \
    scheduled_actions.h \
    shellyrgbw.h \
    build_number.h \
    logger.h \
    preset.h \
    light.h \
    build_number.h \
    logger.h \
    presettask.h \
    weatherdata.h \
    zone.h \
    eventfilter.h \
    sensor.h \
    zwavesocket.h


FORMS    +=

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

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

RESOURCES += qml.qrc
# QMAKE_CXXFLAGS += "-fno-sized-deallocation"
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =
