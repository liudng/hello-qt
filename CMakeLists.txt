# SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

# CMakeLists.txt for the hello project
# This project is a simple hello world application using Qt6.
#
# The project is structured into two main components:
# 1. src/app: Contains the main application code, including the main window and entry point.
# 2. src/core: Contains core functionalities and logic that can be reused across different
#    parts of the application.

cmake_minimum_required(VERSION 3.31)

project(
    hello 
    VERSION 0.1.0
    DESCRIPTION "A simple hello world project"
    HOMEPAGE_URL "https://github.com/liudng/hello-qt"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)
qt_standard_project_setup(
    REQUIRES 6.8
    I18N_SOURCE_LANGUAGE en
    I18N_TRANSLATED_LANGUAGES zh_CN
)

add_subdirectory(src/app)
add_subdirectory(src/core)
add_subdirectory(src/filebrowser)
add_subdirectory(src/texteditor)
