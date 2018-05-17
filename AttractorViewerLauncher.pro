QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AttractorViewerLauncher
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        launcher.cpp

HEADERS += \
        launcher.h
