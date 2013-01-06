cmake_minimum_required(VERSION 2.8)


include(PkgConfigInstallConfiguration)

configure_file("speechcontrol.pc.in" "${PROJECT_BINARY_DIR}/src/lib/speechcontrol.pc" @ONLY)

install(FILES "${PROJECT_SOURCE_DIR}/res/data/SpeechControl.desktop"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/share/applications")

pkgconfig_install_configuration("${PROJECT_BINARY_DIR}/src/lib/speechcontrol.pc")

add_subdirectory(contents)
