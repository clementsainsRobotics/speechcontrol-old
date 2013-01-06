# - Find ExecInfo on the development system.
# This module finds if ExecInfo is installed and determines where the
# include files and libraries are. It also determines what the name of
# the library is. This code sets the following variables:
#
#  EXECINFO_LIBRARIES           - path to the ExecInfo library
#  EXECINFO_INCLUDE_DIRS        - path to where execinfo.h is found
#
#=============================================================================
# Copyright (c) 2012 Jacky Alcine <jacky.alcine@thesii.org>
#
# This module is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)


if (NOT TARGET uninstall)

    # Check if the template's path has been defined.
    # If not, provide the typical path for it.
    # @todo Should load from a standard path.
    # @todo If standard not found, fallback to this.
    if (NOT DEFINED CMAKE_UNINSTALL_TEMPLATE)
        set(CMAKE_UNINSTALL_TEMPLATE "${CMAKE_SOURCE_DIR}/cmake/Templates/cmake_uninstall.cmake.in")
    endif(NOT DEFINED CMAKE_UNINSTALL_TEMPLATE)
    
    CONFIGURE_FILE(
        "${CMAKE_UNINSTALL_TEMPLATE}"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

    ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake")
endif(NOT TARGET uninstall)