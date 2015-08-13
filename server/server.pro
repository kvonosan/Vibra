#-------------------------------------------------
#
# Project created by QtCreator 2015-08-09T21:20:41
#
#-------------------------------------------------

QT       += core network

QT       -= gui sql

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    player.cpp \
    vk_auth.cpp \
    infinite_world.cpp \
    loader.cpp

win32 {
    INCLUDEPATH += c:/boost_1_58_0/
    LIBS += -Lc:/boost_1_58_0/stage/lib/ \
            -lboost_system-mgw49-mt-1_58 \
            -lws2_32
}

unix {
    INCLUDEPATH += /opt/boost_1_58_0/
    LIBS += -L/opt/boost_1_58_0/stage/lib/ \
            -lboost_system
}

HEADERS += \
    player.h \
    infinite_world.h \
    loader.h \
    vk_auth.h
