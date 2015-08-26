#-------------------------------------------------
#
# Project created by QtCreator 2015-08-09T21:20:41
#
#-------------------------------------------------

QT       += core network sql

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += debug_and_release

TEMPLATE = app


SOURCES += main.cpp \
    player.cpp \
    infinite_world.cpp \
    loader.cpp \
    net.cpp \
    myclient.cpp \
    mytask.cpp \
    myserver.cpp

HEADERS += \
    player.h \
    infinite_world.h \
    loader.h \
    net.h \
    myclient.h \
    mytask.h \
    myserver.h
