# SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

# Get the Git revision
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(GIT_REVISION "${GIT_HASH}")

# Configure the config.h file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
    @ONLY
)

qt_add_executable(
    hello
    main.cpp
)

target_link_libraries(hello PRIVATE
    texteditor
    core
    Qt6::Widgets
)

target_include_directories(hello PRIVATE 
    "${CMAKE_CURRENT_BINARY_DIR}"
)

set_target_properties(hello PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)