cmake_minimum_required(VERSION 2.8)

find_package(SpeechControl)

include_directories(${SPEECHCONTROL_INCLUDE_DIRS})

add_subdirectory(dummy)
add_subdirectory(googlespeechrecognition)
