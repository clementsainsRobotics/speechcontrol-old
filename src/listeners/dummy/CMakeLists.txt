project(speechcontrol-listener-dummy)

include(CMakeProvideUninstallTarget)

file(GLOB_RECURSE SPCHCNTRL_LISTENER_DUMMY_SRCS "*.cpp")
qt4_automoc(${SPCHCNTRL_LISTENER_DUMMY_SRCS})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${SPEECHCONTROL_INCLUDE_DIRS})

add_library(speechcontrol-listener-dummy SHARED ${SPCHCNTRL_LISTENER_DUMMY_SRCS})
target_link_libraries(speechcontrol-listener-dummy ${SPEECHCONTROL_LIBRARIES})

speechcontrol_install_listener(speechcontrol-listener-dummy "dummy")