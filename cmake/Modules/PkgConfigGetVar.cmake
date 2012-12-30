MACRO(PKGCONFIG_GETVAR _package _var _output_variable)
  SET(${_output_variable})

  # if pkg-config has been found
  IF(PKG_CONFIG_FOUND)

    EXEC_PROGRAM(${PKG_CONFIG_EXECUTABLE} ARGS ${_package} --exists RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _pkgconfigDevNull )

    # and if the package of interest also exists for pkg-config, then get the information
    IF(NOT _return_VALUE)

      EXEC_PROGRAM(${PKG_CONFIG_EXECUTABLE} ARGS ${_package} --variable ${_var} OUTPUT_VARIABLE ${_output_variable} )

    ELSE(NOT _return_VALUE)
      MESSAGE(WARNING "${_package} not found.")
    ENDIF(NOT _return_VALUE)

  ELSE(PKG_CONFIG_FOUND)
    MESSAGE(ERROR "PkgConfig not found.")
  ENDIF(PKG_CONFIG_FOUND)

ENDMACRO(PKGCONFIG_GETVAR _package _var _output_variable)