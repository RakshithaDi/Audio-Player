#-------------------------------------------------
#
# Project created by QtCreator 2016-06-29T11:25:56
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimplePlayer
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

QMAKE_CXXFLAGS += -std=gnu++11

RESOURCES += \
    buttons.qrc
