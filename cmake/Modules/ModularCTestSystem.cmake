# - Provides a modular architecture for CTest in CMake.
#
# This module provides developers and testers alike with a nifty way of testing
# applications with multiple sources. This allows for quick integration with
# systems that love to do a lot of unit testing.s
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

    # Add a meta-target for all tests.
    add_custom_target(tests)

    # Load the testing template.
    if (NOT DEFINED CTEST_TEMPLATE)
        message(SEND_ERROR "No template was defined in CTEST_TEMPLATE to use for the test executables!")
    elseif(NOT DEFINED CTEST_TEMPLATE)
        
    endif(NOT DEFINED CTEST_TEMPLATE)
endif(BUILD_TESTING EQUAL ON)