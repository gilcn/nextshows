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

FORMS       += ui/mainwindow.ui                 \
               dialogs/ui/aboutdialog.ui        \
               dialogs/ui/settingsdialog.ui     \
               dialogs/settings/ui/findshows.ui \
               dialogs/settings/ui/misc.ui

HEADERS     += version.h                     \
               mainwindow.h                  \
               systrayicon.h                 \
               widgets/nscreditscroller.h    \
               widgets/nslineedit.h          \
               dialogs/about.h               \
               dialogs/settings.h            \
               dialogs/settings/categories.h \
               dialogs/settings/findshows.h  \
               dialogs/settings/misc.h       \
               libs/abstractprovider.h       \
               libs/animatedimage.h          \
               libs/getdata.h                \
               libs/tvrageprovider.h

SOURCES     += main.cpp                        \
               mainwindow.cpp                  \
               systrayicon.cpp                 \
               widgets/nscreditscroller.cpp    \
               widgets/nslineedit.cpp          \
               dialogs/about.cpp               \
               dialogs/settings.cpp            \
               dialogs/settings/categories.cpp \
               dialogs/settings/findshows.cpp  \
               dialogs/settings/misc.cpp       \
               libs/abstractprovider.cpp       \
               libs/animatedimage.cpp          \
               libs/getdata.cpp                \
               libs/tvrageprovider.cpp

TRANSLATIONS = nextshows_fr.ts


# EOF - vim:ts=4:sw=4:et:
