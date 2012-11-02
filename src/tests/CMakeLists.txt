cmake_minimum_required(VERSION 2.8)
project(SpeechControlTests)

# Set some global test variables.
set(TEST_LIBRARIES ${SPCHCNTRL_LIB_LIBRARIES} ${QT_QTTEST_LIBRARY} speechcontrol)
set(TEST_INCLUDE_DIRS ${SPCHCNTRL_LIB_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/src" ${QT_QTTEST_INCLUDE_DIRS})
set(TEST_COMPILE_DEFINTIONS ${SPCHCNTRL_LIB_COMPILE_DEFINITIONS})
set(TEST_COMPILE_FLAGS ${SPCHCNTRL_LIB_COMPILE_FLAGS})
set(TEST_TEMPLATE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/TestTemplate.cmake.in")

# Add the needed tests.
ctest_implement_test("init.cpp" ${TEST_TEMPLATE_PATH})