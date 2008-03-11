TEMPLATE     = app
DESTDIR      = bin
TARGET       = tvragesearch

DEPENDPATH  += libs
OBJECTS_DIR  = build
MOC_DIR      = build
UI_DIR       = build
RCC_DIR      = build

QT          += network xml

FORMS       += ui/tvragesearch.ui

HEADERS     +=          tvragesearch.h   animatedimage.h   tvrageparser.h
SOURCES     += main.cpp tvragesearch.cpp animatedimage.cpp tvrageparser.cpp

RESOURCES    = pics/pics.qrc

TRANSLATIONS = tvragesearch_en.ts tvragesearch_fr.ts
