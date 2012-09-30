# - Provides a modular architecture for CTest in CMake.
#
# This module provides developers and testers alike with a nifty way of testing
# applications with multiple sources. This allows for quick integration with
# systems that love to do a lot of unit testing.
#
# The following variables MUST be defined before including this module:
#
# - CTEST_META_TEMPLATE: The template file that'd be used to render all of the tests.
# - CTEST_META_TEST_DIR: The directory that contains all of the sources to be used as
#       core files for the template.
# - CTEST_META_TEST_SUFFIX: The pattern of the file to look for. Defaults to (*.cpp)
# - CTEST_META_CONFIG_DIR: The directory that contains additionial configuration information
#       for each test.
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

cmake_minimum_required(VERSION 2.8)

include(CTest)

if (BUILD_TESTING EQUAL ON)
    # Check if the suffix regex is set.
    if (NOT DEFINED CTEST_META_TEST_SUFFIX)
        set(CTEST_META_TEST_SUFFIX "*.cpp")
    endif(NOT DEFINED CTEST_META_TEST_SUFFIX)

    # Add a meta-target for all tests.
    add_custom_target(tests)

    # Load the testing template.
    if (NOT DEFINED CTEST_TEMPLATE)
        message(SEND_ERROR "No template was defined in CTEST_TEMPLATE to use for the test executables!")
    endif(NOT DEFINED CTEST_TEMPLATE)
    file(READ ${CTEST_TEMPLATE} _CTEST_BUILD_TEMPLATE)

    # Set up build directory.
    set(_test_cmake_output_dir "${CMAKE_CURRENT_BINARY_DIR}")
    message(STATUS ${_test_cmake_output_dir})

    # Loop over each file for testing.
    file(GLOB _test_file ${CTEST_META_TEST_DIR} ${CTEST_META_TEST_SUFFIX})
    foreach(_test_file ${_test_files})

    endforeach(_test_file ${_test_files})

endif(BUILD_TESTING EQUAL ON)