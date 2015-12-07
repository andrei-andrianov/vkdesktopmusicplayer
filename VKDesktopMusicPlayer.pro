#-------------------------------------------------
#
# Project created by QtCreator 2015-11-07T02:56:37
#
#-------------------------------------------------

QT       += core \
            gui \
            webkit\
            webkitwidgets \
            xml \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VKDesktopMusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        loginwidget.cpp \
    playerwidget.cpp \
    customlistwidgetitemview.cpp \
    lastfmloginwidget.cpp \
    lyricswidget.cpp \
    aboutwidget.cpp

HEADERS  += loginwidget.h \
    playerwidget.h \
    customlistwidgetitemview.h \
    lastfmloginwidget.h \
    lyricswidget.h \
    aboutwidget.h

FORMS    += loginwidget.ui \
    playerwidget.ui \
    customlistwidgetitemview.ui \
    lastfmloginwidget.ui \
    lyricswidget.ui \
    aboutwidget.ui

RESOURCES +=
