project(plasma-applet-LayoutTestApplet)

set(layouttestapplet_applet_SRCS
    layouttestapplet.cpp)

kde4_add_plugin(plasma_applet_layouttestapplet
                ${layouttestapplet_applet_SRCS})

target_link_libraries(plasma_applet_layouttestapplet
                      ${KDE4_KIO_LIBS}
                      ${PLASMA_LIBS})

install(TARGETS plasma_applet_layouttestapplet         DESTINATION ${PLUGIN_INSTALL_DIR}  )
install(FILES   plasma-applet-layouttestapplet.desktop DESTINATION ${SERVICES_INSTALL_DIR})
