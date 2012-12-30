cmake_minimum_required(VERSION 2.8)
project(SpeechControlDaemon)

include_directories(${SPCHCNTRL_INCLUDE_DIRS})

file(GLOB SPCHCNTRL_DAEMON_SOURCES "*.cpp")
configure_file("${CMAKE_SOURCE_DIR}/src/global.hpp.in" "global.hpp")

add_executable(speechcontrold ${SPCHCNTRL_DAEMON_SOURCES})
