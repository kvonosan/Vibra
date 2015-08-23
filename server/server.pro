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
