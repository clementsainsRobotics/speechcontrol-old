include(SpeechControlDefaults)

macro(speechcontrol_install_plugin _plugin_target _plugin_id)
    install(TARGETS ${_plugin_target}
            DESTINATION ${SPCHCNTRL_PLUGINS_LIB_INSTALL_DIR})

    install(FILES "${PROJECT_SOURCE_DIR}/data/${_plugin_id}.spec"
            DESTINATION ${SPCHCNTRL_PLUGINS_SPEC_INSTALL_DIR})

    if (KDE4_FOUND)
        install(TARGETS ${_plugin_target}
                DESTINATION "${PLUGIN_INSTALL_DIR}/plugins/speechcontrol")

        list(APPEND SPCHCNTRL_PLUGINS_LIB_INSTALL_DIR "${PLUGIN_INSTALL_DIR}/plugins/speechcontrol")
        list(REMOVE_DUPLICATES SPCHCNTRL_PLUGINS_LIB_INSTALL_DIR)
    endif (KDE4_FOUND)

endmacro(speechcontrol_install_plugin _plugin_target)