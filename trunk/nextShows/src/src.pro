TEMPLATE     = app

# Show the current SVN rev. if available
SVNVERSION=$$system(svnversion -n)
!isEmpty(SVNVERSION) {
    !contains(SVNVERSION, exported) {
        DEFINES += NS_SVNVERSION=$${SVNVERSION}
    }
}

CONFIG      += warn_on debug_and_release

#### QMAKE_CXXFLAGS += -pedantic

QT          += network xml

bindir       = ../Build
builddir     = ../Build
DESTDIR      = $${bindir}
OBJECTS_DIR  = $${builddir}
MOC_DIR      = $${builddir}
UI_DIR       = $${builddir}
RCC_DIR      = $${builddir}
TARGET       = nextShows

DEPENDPATH  += libs

RESOURCES    = pics/nextshows.qrc

FORMS       += ui/mainwindow.ui  \
               ui/aboutdialog.ui \
               ui/configdialog.ui

HEADERS     += version.h               \
               mainwindow.h            \
               systrayicon.h           \
               aboutdialog.h           \
               configdialog.h          \
               config/configpanels.h   \
               libs/animatedimage.h    \
               libs/tvrageparser.h

SOURCES     += main.cpp                \
               mainwindow.cpp          \
               systrayicon.cpp         \
               aboutdialog.cpp         \
               configdialog.cpp        \
               config/configpanels.cpp \
               libs/animatedimage.cpp  \
               libs/tvrageparser.cpp

#### TRANSLATIONS = XXXX_en.ts XXXX_fr.ts


# EOF - vim:ts=4:sw=4:et:
