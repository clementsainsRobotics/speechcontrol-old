# Try to find PocketSphinx
# POCKETSPHINX_FOUND
# POCKETSPHINX_INCLUDE_DIRS
# POCKETSPHINX_LIBRARIES
# POCKETSPHINX_DEFINITIONS
# POCKETSPHINX_MODELDIR

find_package(PkgConfig)
pkg_check_modules(PC_POCKETSPHINX QUIET pocketsphinx)
set(POCKETSPHINX_DEFINITIONS ${PC_POCKETSPHINX_CFLAGS_OTHER})

find_path(POCKETSPHINX_INCLUDE_DIR pocketsphinx.h
    HINTS ${PC_POCKETSPHINX_INCLUDEDIR} ${PC_POCKETSPHINX_INCLUDE_DIRS})

find_library(POCKETSPHINX_LIBRARY NAMES pocketsphinx
    HINTS ${PC_POCKETSPHINX_LIBDIR} ${PC_POCKETSPHINX_LIBRARY_DIRS})

find_package(SphinxBase REQUIRED)
set(POCKETSPHINX_INCLUDE_DIRS ${POCKETSPHINX_INCLUDE_DIR}
    ${SPHINXBASE_INCLUDE_DIRS})
set(POCKETSPHINX_LIBRARIES ${POCKETSPHINX_LIBRARY} ${SPHINXBASE_LIBRARIES})

mark_as_advanced(POCKETSPHINX_INCLUDE_DIR POCKETSPHINX_LIBRARY)

execute_process(COMMAND ${PKGCONFIG_EXECUTABLE} pocketsphinx --variable=modeldir RESULT_VARIABLE POCKETSPHINX_MODELDIR)


## Report information back to the developer about it's state.
if (POCKETSPHINX_LIBRARY STREQUAL "POCKETSPHINX_LIBRARY-NOTFOUND")
    message(WARNING "PocketSphinx library not found.")
else (POCKETSPHINX_LIBRARY STREQUAL "POCKETSPHINX_LIBRARY-NOTFOUND")
    message(STATUS "Found PocketSphinx library: ${POCKETSPHINX_LIBRARY}")
endif (POCKETSPHINX_LIBRARY STREQUAL "POCKETSPHINX_LIBRARY-NOTFOUND")

if (POCKETSPHINX_INCLUDE_DIR STREQUAL "POCKETSPHINX_INCLUDE_DIR-NOTFOUND")
    message(WARNING "PocketSphinx includes not found.")
else (POCKETSPHINX_INCLUDE_DIR STREQUAL "POCKETSPHINX_INCLUDE_DIR-NOTFOUND")
    message(STATUS "Found PocketSphinx includes: ${POCKETSPHINX_INCLUDE_DIR}")
endif (POCKETSPHINX_INCLUDE_DIR STREQUAL "POCKETSPHINX_INCLUDE_DIR-NOTFOUND")