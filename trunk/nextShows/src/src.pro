TEMPLATE     = app

# Show the current SVN rev. if available
SVNVERSION=$$system(svnversion -n)
!isEmpty(SVNVERSION) {
    !contains(SVNVERSION, exported) {
        DEFINES += SVN_VERSION=$${SVNVERSION}
    }
}

#### QT          += network xml

bindir       = ../bin
builddir     = ../build
DESTDIR      = $${bindir}
OBJECTS_DIR  = $${builddir}
MOC_DIR      = $${builddir}
UI_DIR       = $${builddir}
RCC_DIR      = $${builddir}
TARGET       = nextShows

DEPENDPATH  += libs

RESOURCES    = pics/nextshows.qrc

FORMS       += ui/mainwindow.ui ui/aboutdialog.ui

SOURCES     += main.cpp
HEADERS     += version.h

HEADERS     += mainwindow.h   aboutdialog.h
SOURCES     += mainwindow.cpp aboutdialog.cpp

HEADERS     += config/configdialog.h
SOURCES     += config/configdialog.cpp

#### TRANSLATIONS = XXXX_en.ts XXXX_fr.ts
