
QT       += multimedia widgets core multimediawidgets positioning
QT       -= gui

TARGET = LenovoFirmware
TEMPLATE = app

CONFIG   -= console
CONFIG   -= app_bundle

RC_FILE = resources.rc

SOURCES += \
    main.cpp \
    core.cpp \
    camera.cpp \
    painter.cpp \
    global.cpp \
    network.cpp \
    remove.cpp \
    install.cpp

HEADERS += \
    core.h \
    camera.h \
    painter.h \
    global.h \
    network.h \
    remove.h \
    install.h
