SET(nextShows_MOC_HDRS
    mainwindow.h
    systrayicon.h
    widgets/nscreditscroller.h
    widgets/nslineedit.h
    widgets/nslistwidget.h
    widgets/nstreewidget.h
    dialogs/about.h
    dialogs/settings.h
    dialogs/settings/categories.h
    dialogs/settings/findshows.h
    dialogs/settings/options.h
    libs/animatedimage.h
    libs/datafetcher.h
    libs/dataprovider.h
)

SET(nextShows_SRCS
    main.cpp
    mainwindow.cpp
    systrayicon.cpp
    widgets/nscreditscroller.cpp
    widgets/nslineedit.cpp
    widgets/nslistwidget.cpp
    widgets/nstreewidget.cpp
    dialogs/about.cpp
    dialogs/settings.cpp
    dialogs/settings/categories.cpp
    dialogs/settings/findshows.cpp
    dialogs/settings/options.cpp
    libs/animatedimage.cpp
    libs/dbinterface.cpp
    libs/datafetcher.cpp
    libs/dataprovider.cpp
    libs/tvrageparser.cpp
)

SET(nextShows_UIS
    ui/mainwindow.ui
    dialogs/ui/aboutdialog.ui
    dialogs/ui/settingsdialog.ui
    dialogs/settings/ui/findshows.ui
    dialogs/settings/ui/options.ui
)

SET(nextShows_RCS
    pixmaps/nextshows.qrc
)

INCLUDE( ${QT_USE_FILE} )
  
QT4_ADD_RESOURCES(nextShows_RC_SRCS ${nextShows_RCS})

QT4_WRAP_UI(nextShows_UI_HDRS ${nextShows_UIS})

QT4_WRAP_CPP(nextShows_MOC_SRCS ${nextShows_MOC_HDRS})

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(nextShows ${nextShows_SRCS} ${nextShows_MOC_SRCS} ${nextShows_RC_SRCS} ${nextShows_UI_HDRS})

TARGET_LINK_LIBRARIES(nextShows ${QT_LIBRARIES})
