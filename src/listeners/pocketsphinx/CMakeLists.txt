project(speechcontrol-listener-pocketsphinx)

include(CMakeProvideUninstallTarget)

file(GLOB_RECURSE SPCHCNTRL_LISTENER_POCKETSPHINX_SRCS "*.cpp")
qt4_automoc(${SPCHCNTRL_LISTENER_POCKETSPHINX_SRCS})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${SPEECHCONTROL_INCLUDE_DIRS})
include_directories("${CMAKE_SOURCE_DIR}/src/daemon")

add_library(speechcontrol-listener-pocketsphinx SHARED ${SPCHCNTRL_LISTENER_POCKETSPHINX_SRCS})
target_link_libraries(speechcontrol-listener-pocketsphinx ${SPEECHCONTROL_LIBRARIES})

speechcontrol_install_listener(speechcontrol-listener-pocketsphinx "pocketsphinx")