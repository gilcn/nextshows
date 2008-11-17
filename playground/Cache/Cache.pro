TEMPLATE = app
TARGET =
DEPENDPATH += . src ui
INCLUDEPATH += . src
QT += sql
HEADERS += src/cache.h src/mainwindow.h src/nextshows.h
FORMS += ui/mainwindow.ui
SOURCES += src/cache.cpp src/main.cpp src/mainwindow.cpp
