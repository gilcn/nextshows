TEMPLATE     = app

bindir       = ../bin
builddir     = ../build

DESTDIR      = $${bindir}
TARGET       = nextShows

OBJECTS_DIR  = $${builddir}
MOC_DIR      = $${builddir}
UI_DIR       = $${builddir}
RCC_DIR      = $${builddir}

DEPENDPATH  += libs

QT          += network xml

;FORMS       += ui/XXXX.ui

HEADERS     += mainwindow.h
SOURCES     += mainwindow.cpp main.cpp

;RESOURCES    = pics/XXXX.qrc

;TRANSLATIONS = XXXX_en.ts XXXX_fr.ts
