TEMPLATE     = app
DESTDIR      = bin
TARGET       = tvragesearch

DEPENDPATH  += libs
OBJECTS_DIR  = build
MOC_DIR      = build
UI_DIR       = build
RCC_DIR      = build

QT          += network

FORMS       += ui/tvragesearch.ui

HEADERS     +=          tvragesearch.h   animatedimage.h
SOURCES     += main.cpp tvragesearch.cpp animatedimage.cpp

RESOURCES    = pics/pics.qrc
