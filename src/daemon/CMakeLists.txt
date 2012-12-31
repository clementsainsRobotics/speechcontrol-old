cmake_minimum_required(VERSION 2.8)
project(SpeechControlDaemon)

file(GLOB_RECURSE SPCHCNTRL_DAEMON_SOURCES "*.cpp")
qt4_automoc(${SPCHCNTRL_DAEMON_SOURCES})

include_directories(${SPCHCNTRL_INCLUDE_DIRS} "${CMAKE_BINARY_DIR}/src/daemon")
configure_file("${CMAKE_SOURCE_DIR}/src/global.hpp.in" "global.hpp")


add_executable(speechcontrold ${SPCHCNTRL_DAEMON_SOURCES})

target_link_libraries(speechcontrold ${SPCHCNTRL_LIBRARIES})
