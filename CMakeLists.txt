project(SpeechControl)
cmake_minimum_required(VERSION 2.8)

# Incorporate our custom CMake modules.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

## Required packages
find_package(PkgConfig 0.2 REQUIRED)
find_package(Qt4 4.7 COMPONENTS
  QtCore
  REQUIRED)

include(SpeechControlDefaults)
include(SpeechControlMacros)
include(CTestMacroExtras)

## variables
set(PROJECT_VERSION "0.1")
set(SPCHCNTRL_BUILDING ON)
set(SPCHCNTRL_CMAKE_SDIR "${PROJECT_SOURCE_DIR}/cmake")
set(SPCHCNTRL_INCLUDE_DIRS ${QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR})
set(SPCHCNTRL_BUILD_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_BINARY_DIR}/src")
set(SPCHCNTRL_LIBRARIES ${QT_QTCORE_LIBRARY})

## The subdirectories, order's vital here.
add_subdirectory(cmake)
add_subdirectory(res)
add_subdirectory(src)
add_subdirectory(doc)