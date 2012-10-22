find_package(PythonLibs REQUIRED)

INCLUDE_DIRECTORIES(
    ${PYTHON_INCLUDE_PATH}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${SPCHCNTRL_INCLUDE_DIRS}
)

# Use this as a guide:
# https://github.com/OpenKinect/libfreenect/blob/master/wrappers/python/CMakeLists.txt

find_program(CYTHON_EXECUTABLE cython)
if(NOT CYTHON_EXECUTABLE)
    message(ERROR "Cython not found, it is necessary for Python bindings.")
endif()

# How to Cython the .pyx file
set(CYTHON_INCLUDE_DIRS
    "-I${PROJECT_SOURCE_DIR}/src"
    "-I${CMAKE_CURRENT_SOURCE_DIR}"
)
add_custom_command(OUTPUT speechcontrol.cpp
  COMMAND
  ${CYTHON_EXECUTABLE} -o speechcontrol.cpp -f ${CYTHON_INCLUDE_DIRS} --cplus "${CMAKE_CURRENT_SOURCE_DIR}/libspeechcontrol/speechcontrol.pyx"
  DEPENDS "libspeechcontrol/speechcontrol.pyx"
)

# speechcontrol Python bindings
ADD_LIBRARY(speechcontrol_cython SHARED
    speechcontrol.cpp
)

#TARGET_LINK_LIBRARIES(speechcontrol_cython
#)

SET_TARGET_PROPERTIES(speechcontrol_cython PROPERTIES
    PREFIX ""
    OUTPUT_NAME speechcontrol
)

INSTALL (TARGETS speechcontrol_cython LIBRARY DESTINATION "${DATADIR}/python/")

