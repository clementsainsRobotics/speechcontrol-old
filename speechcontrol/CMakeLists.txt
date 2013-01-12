cmake_minimum_required(VERSION 2.8)

add_subdirectory(new)
if(WITH_OLD)
    add_subdirectory(old)
endif()
