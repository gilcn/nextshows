project(plasma-dataengine-nextshows)

find_package(KDE4 REQUIRED)
find_package(Plasma REQUIRED)

include(KDE4Defaults)

set(dataengine_nextshows_SRCS
    nextshowsengine.cpp
    tvrageparser.cpp)

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR}
                    ${KDE4_INCLUDES}
                    ${QT_QTNETWORK_INCLUDES}
                    ${QT_QTXML_INCLUDES}
                    ${PLASMA_INCLUDE_DIR})

kde4_add_plugin(plasma_engine_nextshows
                ${dataengine_nextshows_SRCS})

target_link_libraries(plasma_engine_nextshows
                      ${KDE4_KIO_LIBS}
                      ${PLASMA_LIBS}
                      ${QT_QTNETWORK_LIBS}
                      ${QT_QTXML_LIBS})

install(TARGETS plasma_engine_nextshows DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-dataengine-nextshows.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
