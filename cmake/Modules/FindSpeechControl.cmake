# - Find the development files for SpeechControl.
# This module finds if SphinxBase is installed and determines where the
# include files and libraries are. It also determines what the name of
# the library is. This code sets the following variables:
#
#  SPEECHCONTROL_LIBRARIES           - path to the SphinxBase library
#  SPEECHCONTROL_INCLUDE_DIRS        - path to where sphinxbase.h is found
#
#=============================================================================
# Copyright (c) 2013 Jacky Alcine <jacky.alcine@thesii.org>
#
# This module is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

include(SpeechControlDefaults)
include(SpeechControlMacros)

set(SPEECHCONTROL_LIBRARIES ${SPCHCNTRL_LIBRARIES})
set(SPEECHCONTROL_INCLUDE_DIRS ${SPCHCNTRL_INCLUDE_DIR} ${SPCHCNTRL_INCLUDE_DIRS})