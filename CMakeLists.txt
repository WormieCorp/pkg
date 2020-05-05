cmake_minimum_required(VERSION 3.5.0)

set(_description "Simple program that translates/transforms arguments between different package managers.")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules;${CMAKE_MODULE_PATH}")

project(pkg-manager-translator VERSION 0.1.0 DESCRIPTION "${_description}" HOMEPAGE_URL "https://github.com/WormieCorp/pkg-manager-translator" LANGUAGES C)

# Custom include
set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT Deps)
include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)

# Cached Configurations
option(BUILD_SHARED_LIBS "Build shared libraries instead of static ones" ON)

# Definitions for all sub projects
add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# Subdirectories
add_subdirectory(src)
add_subdirectory(tests)
