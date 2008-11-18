TEMPLATE = app
TARGET =
DEPENDPATH += . src ui
INCLUDEPATH += . src
QT += sql
HEADERS += src/dbinterface.h src/mainwindow.h src/nextshows.h
FORMS += ui/mainwindow.ui
SOURCES += src/dbinterface.cpp src/main.cpp src/mainwindow.cpp
