TEMPLATE     = app

# Show the current SVN rev. if available
SVNVERSION=$$system(svnversion -n)
!isEmpty(SVNVERSION) {
    !contains(SVNVERSION, exported) {
        DEFINES += NS_SVNVERSION=$${SVNVERSION}
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

HEADERS     += version.h \
               mainwindow.h \
               aboutdialog.h \
               config/configdialog.h

SOURCES     += main.cpp \
               mainwindow.cpp \
               aboutdialog.cpp \
               config/configdialog.cpp

#### TRANSLATIONS = XXXX_en.ts XXXX_fr.ts
