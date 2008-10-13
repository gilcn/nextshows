set(nextShows_SRCS main.cpp
                   nextshowsmain.cpp)

kde4_add_ui_files(nextShows_SRCS ui/nextshows.ui)

kde4_add_executable(nextShows ${nextShows_SRCS})

target_link_libraries(nextShows ${KDE4_KDEUI_LIBS})

install(TARGETS nextShows DESTINATION ${BIN_INSTALL_DIR})
install(FILES nextShowsui.rc DESTINATION ${DATA_INSTALL_DIR}/nextShows)
