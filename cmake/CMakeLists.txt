cmake_minimum_required(VERSION 2.8)

include(CMakeInstallModules)
file(GLOB SPCHCNTRL_CMAKE_FILES "Modules/*.cmake")

cmake_install_modules("${SPCHCNTRL_CMAKE_FILES}")
cmake_install_modules("Templates/cmake_uninstall.cmake.in")