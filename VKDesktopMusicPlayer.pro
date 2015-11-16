#-------------------------------------------------
#
# Project created by QtCreator 2015-11-07T02:56:37
#
#-------------------------------------------------

QT       += core gui webkitwidgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VKDesktopMusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        loginwidget.cpp \
    playerwidget.cpp \
    customlistwidgetitemview.cpp

HEADERS  += loginwidget.h \
    playerwidget.h \
    customlistwidgetitemview.h

FORMS    += loginwidget.ui \
    playerwidget.ui \
    customlistwidgetitemview.ui
