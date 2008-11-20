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

QT          += network xml sql

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

FORMS       += ui/mainwindow.ui                 \
               dialogs/ui/aboutdialog.ui        \
               dialogs/ui/settingsdialog.ui     \
               dialogs/settings/ui/findshows.ui \
               dialogs/settings/ui/options.ui

HEADERS     += nextshows.h                   \
               mainwindow.h                  \
               systrayicon.h                 \
               widgets/nscreditscroller.h    \
               widgets/nslineedit.h          \
               widgets/nslistwidget.h        \
               widgets/nstreewidget.h        \
               dialogs/about.h               \
               dialogs/settings.h            \
               dialogs/settings/categories.h \
               dialogs/settings/findshows.h  \
               dialogs/settings/options.h    \
               libs/animatedimage.h          \
               libs/dbinterface.h            \
               libs/datafetcher.h            \
               libs/dataprovider.h           \
               libs/tvrageparser.h

SOURCES     += main.cpp                        \
               mainwindow.cpp                  \
               systrayicon.cpp                 \
               widgets/nscreditscroller.cpp    \
               widgets/nslineedit.cpp          \
               widgets/nslistwidget.cpp        \
               widgets/nstreewidget.cpp        \
               dialogs/about.cpp               \
               dialogs/settings.cpp            \
               dialogs/settings/categories.cpp \
               dialogs/settings/findshows.cpp  \
               dialogs/settings/options.cpp    \
               libs/animatedimage.cpp          \
               libs/dbinterface.cpp            \
               libs/datafetcher.cpp            \
               libs/dataprovider.cpp           \
               libs/tvrageparser.cpp

TRANSLATIONS = nextshows_fr.ts


# EOF - vim:ts=4:sw=4:et:
