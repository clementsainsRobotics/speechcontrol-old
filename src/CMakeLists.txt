cmake_minimum_required(VERSION 2.8)

configure_file("global.hpp.in" "global.hpp")

add_subdirectory(daemon)
add_subdirectory(tests)
add_subdirectory(kde)
