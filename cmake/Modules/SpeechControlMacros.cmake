include(SpeechControlDefaults)

macro(speechcontrol_install_listener _listener_target _listener_name)
    install(TARGETS ${_listener_target}
            DESTINATION ${SPCHCNTRL_LISTENERS_LIB_INSTALL_DIR})

    install(FILES "${CMAKE_SOURCE_DIR}/data/listeners/${_listener_name}.spec"
            DESTINATION ${SPCHCNTRL_LISTENERS_SPEC_INSTALL_DIR})
endmacro(speechcontrol_install_listener _listener_target _listener_name)