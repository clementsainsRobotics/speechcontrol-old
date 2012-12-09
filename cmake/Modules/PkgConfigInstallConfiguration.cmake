macro(pkgconfig_install_configuration PATH)
    install(FILES "${PATH}"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkgconfig")
endmacro(pkgconfig_install_configuration PATH)
