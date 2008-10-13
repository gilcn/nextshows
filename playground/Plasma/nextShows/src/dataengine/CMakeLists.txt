project(plasma-dataengine-nextshows)

set(dataengine_nextshows_SRCS
    nextshowsengine.cpp
    tvrageparser.cpp)

kde4_add_plugin(plasma_engine_nextshows
                ${dataengine_nextshows_SRCS})

target_link_libraries(plasma_engine_nextshows
                      ${KDE4_KIO_LIBS}
                      ${PLASMA_LIBS})

install(TARGETS plasma_engine_nextshows DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-dataengine-nextshows.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
