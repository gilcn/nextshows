TEMPLATE     = app
TARGET       = ../tvragesearch
DEPENDPATH  += . ui libs
INCLUDEPATH += .

FORMS       += ui/TvRageSearch.ui

HEADERS     +=          TvRageSearch.h   AnimImage.h
SOURCES     += main.cpp TvRageSearch.cpp AnimImage.cpp

RESOURCES    = pics/pics.qrc
