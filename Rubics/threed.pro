QT       += core gui widgets

TARGET = threed

CONFIG += console

SOURCES += main.cpp

SOURCES += \
    mainwidget.cpp \
    Mesh.cpp \
    OBJ.cpp

HEADERS += \
    mainwidget.h \
    Mesh.h \
    OBJ.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

