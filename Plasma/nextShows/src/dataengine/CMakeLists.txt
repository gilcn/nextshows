project(plasma_nextShows_dataengine)

find_package(KDE4 REQUIRED)
find_package(Plasma REQUIRED)

include(KDE4Defaults)

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR}
                    ${KDE4_INCLUDES}
                    ${QT_QTNETWORK_INCLUDES}
                    ${QT_QTXML_INCLUDES}
                    ${PLASMA_INCLUDE_DIR})

set(nextshows_engine_SRCS
    nextshowsengine.cpp
    tvrageparser.cpp)

kde4_add_plugin(plasma_engine_nextshows
                ${nextshows_engine_SRCS})

target_link_libraries(plasma_engine_nextshows
                      ${KDE4_KIO_LIBS}
                      plasma
                      ${QT_QTNETWORK_LIBS}
                      ${QT_QTXML_LIBS})

install(TARGETS plasma_engine_nextshows DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-dataengine-nextshows.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
