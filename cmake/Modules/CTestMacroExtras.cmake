# - Provides some extra cool macros for use with CTest.
#
# This module provides developers and testers alike with a nifty way of testing
# applications with multiple sources. This allows for quick integration with
# systems that love to do a lot of unit testing.
#
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

# Define some targets that'll provide some nifty targets.
add_custom_target(test COMMENT "Building all tests...")

# @fn ctest_clear_build
# Wipes out the test build system.
macro(ctest_clear_build)
    if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/CTestMetaTargets")
        file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/CTestMetaTargets")
    endif(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/CTestMetaTargets")
endmacro(ctest_clear_build)

macro(ctest_add_coverage_support _target)
    set(_compiler_flags "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
    set(_linker_flags "-fprofile-arcs -ftest-coverage")

    get_property(_old_compiler_flags TARGET ${_target} PROPERTY COMPILE_FLAGS)
    get_property(_old_linker_flags TARGET ${_target} PROPERTY LINK_FLAGS)

    if (_old_compiler_flags EQUAL 1)
    set_target_properties(${_target} PROPERTIES
        COMPILE_FLAGS "${_compiler_flags} ${_old_compiler_flags}"
    )
    endif()

    if (_old_linker_flags EQUAL 1)
    set_target_properties(${_target} PROPERTIES
        LINK_FLAGS "${_linker_flags} ${_old_linker_flags}"
    )
    endif()

    target_link_libraries(${_target} gcov)
endmacro(ctest_add_coverage_support _target)

macro(ctest_add_executable _target _sources)
    add_executable("test_${_target}" "${_sources}")

    # Add test and make the meta-test depend on it.
    add_test(NAME "test${_target}"
            COMMAND "$<TARGET_FILE:test_${_target}>")
    add_dependencies(test "test_${_target}")
endmacro(ctest_add_executable _target _sources)

# @fn ctest_implement_test
# Renders a test from a template file.
macro(ctest_implement_test _Sources _Template)
    set(_Sources ${_Sources})
    string(MD5 _Template_Id "${_Sources}")
    string(SUBSTRING ${_Template_Id} 0 6 _Template_Id)
    
    file(READ "${_Template}" _Template_Text)

    string(CONFIGURE "${_Template_Text}" _Template_Text @ONLY)
    set(_path "${CMAKE_CURRENT_BINARY_DIR}/CTestMetaTargets/${_Template_Id}.cmake")

    file(WRITE ${_path} ${_Template_Text})
    include(${_path})

endmacro(ctest_implement_test)
