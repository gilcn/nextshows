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

RESOURCES    = pixmaps/nextshows.qrc

FORMS       += ui/mainwindow.ui             \
               dialogs/ui/aboutdialog.ui    \
               dialogs/ui/settingsdialog.ui \
               settings/ui/findshows.ui     \
               settings/ui/misc.ui

HEADERS     += version.h             \
               mainwindow.h          \
               systrayicon.h         \
               dialogs/about.h       \
               dialogs/settings.h    \
               settings/categories.h \
               settings/findshows.h  \
               settings/misc.h       \
               libs/animatedimage.h  \
               libs/tvrageparser.h

SOURCES     += main.cpp                \
               mainwindow.cpp          \
               systrayicon.cpp         \
               dialogs/about.cpp       \
               dialogs/settings.cpp    \
               settings/categories.cpp \
               settings/findshows.cpp  \
               settings/misc.cpp       \
               libs/animatedimage.cpp  \
               libs/tvrageparser.cpp

#### TRANSLATIONS = XXXX_en.ts XXXX_fr.ts


# EOF - vim:ts=4:sw=4:et:
