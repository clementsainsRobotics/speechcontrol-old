cmake_minimum_required(VERSION 2.8)

configure_file("global.hpp.in" "global.hpp")
include_directories(${CMAKE_CURRENT_DIRECTORY})

add_subdirectory(daemon)
add_subdirectory(listeners)
add_subdirectory(tests)
add_subdirectory(kde)