INCLUDE_DIRECTORIES(
    ${PYTHON_INCLUDE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Use this as a guide:
# https://github.com/OpenKinect/libfreenect/blob/master/wrappers/python/CMakeLists.txt

# How to Cython the .pyx file
set(CYTHON_INCLUDE_DIRS 
    "${PROJECT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
add_custom_command(OUTPUT libspeechcontrol/speechcontrol.cpp
  COMMAND
  ${CYTHON_EXECUTABLE} -o libspeechcontrol/speechcontrol.cpp -f -I ${CYTHON_INCLUDE_DIRS} --cplus "${CMAKE_CURRENT_SOURCE_DIR}/libspeechcontrol/speechcontrol.pyx"
  DEPENDS "libspeechcontrol/speechcontrol.pyx"
)

# speechcontrol Python bindings
ADD_LIBRARY(speechcontrol_cython SHARED
    libspeechcontrol/speechcontrol.cpp
)

#TARGET_LINK_LIBRARIES(speechcontrol_cython
#)

SET_TARGET_PROPERTIES(speechcontrol_cython PROPERTIES
    PREFIX ""
    OUTPUT_NAME libspeechcontrol/speechcontrol
)

INSTALL (TARGETS speechcontrol_cython LIBRARY DESTINATION "${DATADIR}/python/")

