QT       += core gui widgets

TARGET = boidie

CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp

SOURCES += \
    mainwidget.cpp \
    Boid.cpp \
    Mesh.cpp

HEADERS += \
    mainwidget.h \
    Mesh.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

