TEMPLATE     = app
DESTDIR      = bin
TARGET       = tvragesearch

DEPENDPATH  += libs
OBJECTS_DIR  = build
MOC_DIR      = build
UI_DIR       = build
RCC_DIR      = build

QT          += network

FORMS       += ui/TvRageSearch.ui

HEADERS     +=          TvRageSearch.h   AnimImage.h
SOURCES     += main.cpp TvRageSearch.cpp AnimImage.cpp

RESOURCES    = pics/pics.qrc
