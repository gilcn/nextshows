project(plasma-applet-nextShows)

set(nextshows_applet_SRCS
    nextshowsapplet.cpp)

kde4_add_plugin(plasma_applet_nextshows
                ${nextshows_applet_SRCS})

target_link_libraries(plasma_applet_nextshows
                      ${KDE4_KIO_LIBS}
                      ${PLASMA_LIBS})

install(TARGETS plasma_applet_nextshows DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-applet-nextshows.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
