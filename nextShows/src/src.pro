TEMPLATE     = app

# Show the current SVN rev. if available
SVNVERSION=$$system(svnversion -n)
!isEmpty(SVNVERSION) {
    !contains(SVNVERSION, exported) {
        DEFINES += SVN_VERSION=$${SVNVERSION}
    }
}

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

FORMS       += ui/mainwindow.ui

SOURCES     += main.cpp
HEADERS     += version.h

HEADERS     += mainwindow.h
SOURCES     += mainwindow.cpp

;RESOURCES    = pics/XXXX.qrc

;TRANSLATIONS = XXXX_en.ts XXXX_fr.ts
