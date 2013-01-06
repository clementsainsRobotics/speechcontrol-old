cmake_minimum_required(VERSION 2.8)
project(SpeechControlDaemon)

include(CMakeProvideUninstallTarget)

file(GLOB_RECURSE SPCHCNTRL_DAEMON_SOURCES "*.cpp")
qt4_automoc(${SPCHCNTRL_DAEMON_SOURCES})

include_directories("${CMAKE_SOURCE_DIR}/src/daemon" "${CMAKE_BINARY_DIR}/src")
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${SPCHCNTRL_INCLUDE_DIRS})

add_executable(speechcontrold ${SPCHCNTRL_DAEMON_SOURCES})

target_link_libraries(speechcontrold ${SPCHCNTRL_LIBRARIES})

install(DIRECTORY "listeners"
  DESTINATION "${SPCHCNTRL_INCLUDE_DIR}"
  FILES_MATCHING PATTERN "*.hpp")
	
install(TARGETS speechcontrold
  RUNTIME DESTINATION "${SPCHCNTRL_BIN_DIR}"
  DESTINATION "${SPCHCNTRL_BIN_DIR}"
  COMPONENT bin)