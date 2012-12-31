# - Provides the ability to install extra CMake modules for discovery.
#
# This module provides developers with the ability to add extra CMake 
# modules to the default location that at which CMake modules are discovered.
#
#
#=============================================================================
# Copyright (c) 2012 Jacky Alcine <me@jalcine.me>
#
# This module is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public License 
# as published by the Free Software Foundation; either version 2 of the 
# License, or (at your option) any later version.
#
#=============================================================================
#
#
cmake_minimum_required(VERSION 2.8)


macro(cmake_install_modules CMAKE_MODULES)
  install(FILES ${CMAKE_MODULES}
	  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules"
	  COMPONENT dev)
endmacro(cmake_install_modules CMAKE_MODULES)
