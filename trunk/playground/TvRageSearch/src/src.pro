TEMPLATE     = app
TARGET       = ../tvragesearch
DEPENDPATH  += . ui libs
INCLUDEPATH += .

FORMS       += ui/tvragesearch.ui

HEADERS     +=          tvragesearch.h   AnimImage.h
SOURCES     += main.cpp tvragesearch.cpp AnimImage.cpp

RESOURCES    = pics/pics.qrc
